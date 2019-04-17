/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include <lwrender.h>
#include <lwpanel.h>
#include "Common.h"
#include "LightwaveCommon.h"
#include "DeepCloneFX.h"
#include "DeepCloneObjectPanel.h"

GlobalFunc   *ObjectPanel::_global;
LWPanelFuncs *ObjectPanel::panf = NULL;
LWPanelID ObjectPanel::panel;

int ObjectPanel::tabPosX = 0;
int ObjectPanel::tabPosY = 0;

LWControl *ObjectPanel::mode = NULL;
LWControl *ObjectPanel::sequenceType = NULL;
LWControl *ObjectPanel::edit = NULL;
LWControl *ObjectPanel::objectList = NULL;

static char *modeList[] = {
   "Pieces",
   "Compond Object",
   NULL
};

static char *sequenceList[] = {
   "Cycle",
   "Repeat",
   "Random",
   NULL
};

static char *editList[] = {
   "Add From Layout Selected",
   "Clone Object(s)+",
   "Remove",
   "Remove All",
   NULL
};

void ObjectPanel::drawObjectView(GlobalFunc _glob, LWPanelFuncs* pf, LWPanelID  pan){
	LWPanControlDesc desc;
	LWValue
      ival  = { LWT_INTEGER },
      ival2 = { LWT_INTEGER },
      ival3 = { LWT_INTEGER },
      sval  = { LWT_STRING  },
      pval  = { LWT_POINTER };

	_global = _glob;
	panf    = pf;
	panel   = pan;

	mode = POPDOWN_CTL( panf, panel, "Mode", (const char**)modeList);
	MOVE_CON(mode, tabPosX + 35, tabPosY + 30 );
	
	sequenceType = POPDOWN_CTL( panf, panel, "Sequence Type", (const char**)sequenceList);
	edit = POPDOWN_CTL( panf, panel, "Edit", (const char**)editList);
	
	objectList = LISTBOX_CTL(panf, panel, "Objects To Copy:", 100, 5, objectListName, objectListCount );
	ival.intv.value = 400;
	objectList->set(objectList, CTL_W, &ival);
	ival.intv.value = 250;
	objectList->set(objectList, CTL_H, &ival);

	CON_SETEVENT(edit, groupEditOptionsEvent, NULL);

	PAN_SETMINH(panf, panel,  375);
	PAN_SETH(panf, panel, 375);
}

void ObjectPanel::clearObjectView(){

	ERASE_CON(mode);
	ERASE_CON(sequenceType);
	ERASE_CON(edit);
	ERASE_CON(objectList);

	mode = NULL;
	sequenceType = NULL;
	edit = NULL;
	objectList = NULL;
}

int  ObjectPanel::objectListCount( void *data ){
	return (int)DeepCloneFX::objectToClones.size();
}

char *ObjectPanel::objectListName( void *data, int index ){
   size_t c;

   c = DeepCloneFX::objectToClones.size();

   if(index >= 0 && index < c){
        const char *name = NULL;
        LWItemInfo *iteminfo;
        iteminfo = (LWItemInfo *)panf->globalFun( LWITEMINFO_GLOBAL, GFUSE_TRANSIENT );
		name = iteminfo->name(DeepCloneFX::objectToClones.at(index));
        return (char*)name;
   }else
        return NULL;
}

int ObjectPanel::validSfSceneObject(GlobalFunc *_glSceneFunctions, LWItemID itemid){
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

void ObjectPanel::addSelectedObject(){
	LWValue
			ival  = { LWT_INTEGER };

	LWMessageFuncs* sf_msg;
    LWInterfaceInfo *intinfo;
	//LWItemID itemid;
	LWItemInfo *iteminfo;
	//char str[200];
	int coltype = -1;
	int rigidtype = -1;

	sf_msg = (LWMessageFuncs*)_global( LWMESSAGEFUNCS_GLOBAL, GFUSE_TRANSIENT );
	iteminfo = (LWItemInfo *)_global( LWITEMINFO_GLOBAL, GFUSE_TRANSIENT );
    intinfo  = (LWInterfaceInfo *)_global( LWINTERFACEINFO_GLOBAL, GFUSE_TRANSIENT );
  
	if(!intinfo || !iteminfo)  return;
    
	int itemcounter = 0;

    if(intinfo){
		if(intinfo->selItems[0] == LWITEM_NULL)
			return;
		
		while(intinfo->selItems[itemcounter] != LWITEM_NULL)
		{	
			LWItemID itemid = intinfo->selItems[0];

			if(validSfSceneObject(_global, itemid) != 1){
				itemcounter++;
				continue;
			}

			if(itemid == DeepCloneFX::clonerItem)
				
				continue;

			TempMesh tmesh = buildTempMesh(itemid, _global);
			DeepCloneFX::objectToClones.push_back(itemid);
			DeepCloneFX::objectMeshInfo.push_back(tmesh);

			itemcounter++;
		}
	}
}

void ObjectPanel::groupEditOptionsEvent( LWControl *control, void *data){
	LWValue
			ival  = { LWT_INTEGER };

	 LWCommandFunc *evaluate = ( LWCommandFunc *)_global( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
	int index;
	GET_INT(edit, index);
	
	if(index == 0){
		addSelectedObject();
		REDRAW_CON(objectList);
		evaluate("RedrawNow");
	}else if(index == 1){
		DeepCloneFX::finalizeClone();
		REDRAW_CON(objectList);
		evaluate("RedrawNow");
	}else if(index == 2){
		
	}
}