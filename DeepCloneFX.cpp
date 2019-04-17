/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include <lwserver.h> 
#include <lwgeneric.h>          
#include <lwxpanel.h> 
#include <lwpanel.h>   
#include <lwhost.h>              
#include <stdio.h>
#include <minwindef.h>
#include "DeepCloneMaster.h"
#include "DeepCloneObjectPanel.h"
#include "DeepClonePlacementPanel.h"
#include "LightwaveCommon.h"
#include "DeepCloneFX.h"
#include "DeepCloneVisualizer.h"

//Panels/////////////////////////////////////////////
GlobalFunc *_globalGlobal = NULL;
LWXPanelFuncs *mc_xpanf = NULL;
LWPanelFuncs  *panf     = NULL;
LWCommandFunc *evaluate = NULL;

///Initialize Other stuff///////////////////////////////
LWMessageFuncs *msg; 
LWPanelID panel; 

///////////////////////////////////////////////////////
void DeepCloneFX::finalizeClone(){
	if(objectToClones.size() > 0){
	

		for(Vector3 pos: *DeepCloneFX::points){
			char buffer[200];
			sprintf_s(buffer, sizeof(buffer),"SelectItem %#0X", objectToClones[0]);
			evaluate(buffer);
			evaluate("Clone 1");
			sprintf_s(buffer, sizeof(buffer),"Position %f %f %f", pos.x, pos.y, pos.z);
			evaluate(buffer);
			evaluate("RemoveServer CustomObjHandler 1");
		}

		/*objectToClones.clear();
		objectMeshInfo.clear();*/
	}
}

void DeepCloneFX::initSystem(){

	DeepCloneMasterGraph::_global = _globalGlobal;
	DeepCloneMasterGraph::initialize();

	LWCommandFunc *evaluate  = (LWCommandFunc *)_globalGlobal( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
	LWInterfaceInfo *intinfo = (LWInterfaceInfo *)_globalGlobal( LWINTERFACEINFO_GLOBAL, GFUSE_TRANSIENT );

	char eval[200];
		
	sprintf_s(eval, sizeof(eval),"AddNull __DeepCloneSuperSuperNull__");
	evaluate(eval);

	DeepCloneFX::points = DeepCloneMasterGraph::LinearPlacementGraph::linearPoints.out_Points;

	sprintf_s(eval, sizeof(eval),"ApplyServer CustomObjHandler Colorida_Clone_Visualizer");
	evaluate(eval);
}

void DeepCloneFX::close(){
	panf->close(panel);
}

void DeepCloneFX::initSystem2(){
	DeepCloneMasterGraph::_global = _globalGlobal;
	DeepCloneMasterGraph::initialize();
	DeepCloneFX::points = DeepCloneMasterGraph::LinearPlacementGraph::linearPoints.out_Points;
}

int DeepCloneFX::validSfSceneObject(GlobalFunc *_glSceneFunctions, LWItemID itemid){
	LWItemInfo *iteminfo   = (LWItemInfo *)_glSceneFunctions( LWITEMINFO_GLOBAL, GFUSE_TRANSIENT );
	LWObjectInfo *objinfo  = (LWObjectInfo *)_glSceneFunctions( LWOBJECTINFO_GLOBAL, GFUSE_TRANSIENT );
	
	if(objinfo->numPolygons(itemid) <= 0){
		return 0;
	}

	if((iteminfo->type(UINT2LWITEMID(itemid))) != LWI_OBJECT){
		return 0;
	}

	return 1;
}

int DeepCloneFX::addSelectedObject(){
	LWValue
			ival  = { LWT_INTEGER };

	LWMessageFuncs* sf_msg;
    LWInterfaceInfo *intinfo;
	LWCommandFunc *evaluate;
	//LWItemID itemid;
	LWItemInfo *iteminfo;
	//char str[200];
	int coltype = -1;
	int rigidtype = -1;

	evaluate  = (LWCommandFunc *)_globalGlobal( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
	sf_msg = (LWMessageFuncs*)_globalGlobal( LWMESSAGEFUNCS_GLOBAL, GFUSE_TRANSIENT );
	iteminfo = (LWItemInfo *)_globalGlobal( LWITEMINFO_GLOBAL, GFUSE_TRANSIENT );
    intinfo  = (LWInterfaceInfo *)_globalGlobal( LWINTERFACEINFO_GLOBAL, GFUSE_TRANSIENT );
  
	DeepCloneFX::clonerItem = LWITEM_NULL;

	if(!intinfo || !iteminfo)  return 0;
    
	int itemcounter = 0;

    if(intinfo){
		if(intinfo->selItems[0] == LWITEM_NULL){
			sf_msg->okCancel("Colorida v1.0.1", "You need to select an object first.", NULL);
			return 0;
		}
	
		LWItemID itemid = intinfo->selItems[0];

		if(validSfSceneObject(_globalGlobal, itemid) != 1){
			sf_msg->okCancel("Colorida v1.0.1", "Not an object selected, or no polygons found;", NULL);
			return 0;
		}

		TempMesh tmesh = buildTempMesh(itemid, _globalGlobal);
		DeepCloneFX::objectToClones.push_back(itemid);
		DeepCloneFX::objectMeshInfo.push_back(tmesh);

		char eval[200];

		sprintf_s(eval, sizeof(eval), "ApplyServer CustomObjHandler Colorida_Clone_Visualizer");
		evaluate(eval);
	}

	return 1;
}

////////////////////////////////////////////////////////
LWXPanelID xpan;
int itemPropertiesTabSelection = 0;
int	itemPropertiesTabCurrentlySelected = 0;
static bool windowIsOpen = false;

///Initialize Deep Clone FX Engine//////////////////////
LWItemID DeepCloneFX::clonerItem = LWITEM_NULL;
vector<LWItemID> DeepCloneFX::objectToClones;
vector<TempMesh> DeepCloneFX::objectMeshInfo;
xPointArray DeepCloneFX::points;              

///Controls/////////////////////////////////////////////
LWControl *mainTabControl;
LWControl *borderMainTabControl;
LWControl *placementPanel;

///Tab Position/////////////////////////////////////////
int topTabposX = 0;
int topTabposY = 0;

////////////////////////////////////////////////////////
static char *deepCloneTabs[] = {
   "Placement",
//   "Objects",
   NULL
};

void clearTabs(int index){
	if(index == 0){
		ERASE_CON(placementPanel);
	}else if(index == 1){
		ObjectPanel::clearObjectView();
	}
}

int tabSelEvent(LWControl *control, void *userdata, int indo, BOOL selecting ){
	LWPanControlDesc desc;

	LWValue
      ival  = { LWT_INTEGER};

	int index;
	GET_INT(control, index);

	if(selecting && index > -1){
		itemPropertiesTabSelection = index;
		
		if(itemPropertiesTabSelection == 0){
			if(itemPropertiesTabCurrentlySelected == itemPropertiesTabSelection) return 1;

			clearTabs(itemPropertiesTabCurrentlySelected);

			//LWXPanelID xidGeneral = PlacementPanel::drawLinearPlacementView(_globalGlobal, mc_xpanf);

			placementPanel = XPANEL_CTL( panf, panel, "", xpan );
			MOVE_CON(placementPanel , topTabposX + 35, topTabposY + 30 );
			
			itemPropertiesTabCurrentlySelected = 0;

		}else if(itemPropertiesTabSelection == 1){
			if(itemPropertiesTabCurrentlySelected == itemPropertiesTabSelection) return 1;

			clearTabs(itemPropertiesTabCurrentlySelected);
			ObjectPanel::drawObjectView(_globalGlobal, panf, panel);

			itemPropertiesTabCurrentlySelected = 1;
		}
	}

	return 1;
}

static void onMainPanelClose(LWPanelID panel, void *userdata ){
	if(DeepCloneFX::objectToClones.size() > 0){

		char buffer[500];

		sprintf_s(buffer, sizeof(buffer), "SelectItem %#0X", DeepCloneFX::objectToClones[0]);
		evaluate(buffer);
		evaluate("RemoveServer CustomObjHandler 1");

		DeepCloneFX::objectToClones.clear();
		DeepCloneFX::objectMeshInfo.clear();
	}

	//evaluate("SelectByName __DeepCloneSuperSuperNull__");
	//evaluate("ClearSelected 3");

	windowIsOpen = false;
}

XCALL_( int )
DeepCloneFX( int version, GlobalFunc *global, LWLayoutGeneric *local, void *serverData ){

	if(windowIsOpen)
		return AFUNC_OK;

   LWPanControlDesc desc;
	LWValue
      ival  = { LWT_INTEGER },
      ival2 = { LWT_INTEGER },
      ival3 = { LWT_INTEGER },
      sval  = { LWT_STRING  },
      pval  = { LWT_POINTER };

	if(version != LWLAYOUTGENERIC_VERSION)
		return AFUNC_BADVERSION;

	_globalGlobal = global;

	mc_xpanf = (LWXPanelFuncs*)global( LWXPANELFUNCS_GLOBAL, GFUSE_TRANSIENT );
	panf     = (LWPanelFuncs*)global( LWPANELFUNCS_GLOBAL, GFUSE_TRANSIENT );
	evaluate = ( LWCommandFunc *)global( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
	
	if (!panf || !mc_xpanf) return AFUNC_BADGLOBAL;

	panel = PAN_CREATE(panf, "Colorida v1.0.1");

    mainTabControl = TABCHOICE_CTL(panf, panel, "General", (const char**)deepCloneTabs);

	MOVE_CON( mainTabControl, -30, 0);

	mainTabControl->get( mainTabControl, CTL_X, &ival );
    mainTabControl->get( mainTabControl, CTL_Y, &ival2 );

	topTabposX = ival.intv.value;
	topTabposY = ival2.intv.value;

	ObjectPanel::tabPosX = topTabposX;
	ObjectPanel::tabPosY = topTabposY;

	ival.intv.value = 440;
	mainTabControl->set(mainTabControl, CTL_W, &ival);

	borderMainTabControl = BORDER_CTL(panf, panel, "", 425, 0 );
	MOVE_CON(borderMainTabControl, topTabposX, topTabposY + 18);

	//DeepCloneFX::initSystem();
	DeepCloneFX::initSystem2();
	int rc = DeepCloneFX::addSelectedObject();

	if(!rc) return AFUNC_OK;

	xpan = PlacementPanel::drawLinearPlacementView(global, mc_xpanf);
	placementPanel = XPANEL_CTL(panf, panel, "", xpan);

	panf->open(panel, PANF_NOBUTT);
	//CON_SETEVENT(mainTabControl , tabSelEvent,  NULL);

	windowIsOpen = true;

	panf->set(panel, PAN_USERCLOSE, onMainPanelClose);

    return AFUNC_OK;
}

ServerTagInfo DeepClone_FX_TAGS[] = {
	{ "Colorida", SRVTAG_USERNAME },
	{ "Deep FX/Tools/Colorida", SRVTAG_MENU },
	{ NULL }
};

ServerRecord ServerDesc[] = {
   { LWLAYOUTGENERIC_CLASS, "Colorida_Generic_Main",  (ActivateFunc*)DeepCloneFX, DeepClone_FX_TAGS },
   { LWCUSTOMOBJ_HCLASS, "Colorida_Clone_Visualizer", (ActivateFunc*)DeepCloneVisualizer },
   { NULL }
};