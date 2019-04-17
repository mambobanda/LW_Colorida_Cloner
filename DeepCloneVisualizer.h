/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#pragma once


#include <lwserver.h>
#include <lwhandler.h>
#include <lwrender.h>
#include <lwcustobj.h>
#include <lwhost.h>
#include <stdlib.h>
#include "Vector.h"
#include "Common.h"

static GlobalFunc *_globalVisualizer;

static int color_counter = -1;
static float colors[][4] = {{1.0,1.0,1.0, 1.0}}; 
static int range_color_count = 20;
static float range_colors[20][4] ={ {(float)9/255, (float)26/255, (float)229/255, 0.8f}, 
							 {(float)190/255, (float)1.0,     (float)99/255, 0.8f},
							 {(float)57/255,  (float)85/255,  (float)188/255,0.8f},
							 {(float)102/255, (float)57/255,  (float)157/255,0.8f}, 
							 {(float)174/255, (float)130/255, (float)139/255,0.8f},
							 {(float)125/255, (float)175/255, (float)160/255,0.8f},
							 {(float)250/255, (float)1,       (float)115/255,0.8f}, 
							 {(float)97/255,  (float)85/255,  (float)57/255, 0.8f},
							 {(float)216/255, (float)88/255,  (float)22/255, 0.8f},
							 {(float)249/255, (float)7/255,   (float)29/255, 0.8f},
							 {(float)0,       (float)254/255, (float)173/255,0.8f},
							 {(float)142/255, (float)192/255, (float)81/255, 0.8f},
							 {(float)216/255, (float)87/255,  (float)16/255, 0.8f},
							 {(float)210/255, (float)156/255, (float)167/255,0.8f},
							 {(float)223/255, (float)252/255, (float)182/255,0.8f},
							 {(float)226/255, (float)10/255,  (float)106/255,0.8f}, 
							 {(float)117/255, (float)187/255, (float)120, 0.8f},
							 {(float)77/255,  (float)125/255, (float)45/255, 0.8f},
							 {(float)176/255, (float)12/255,  (float)117/255, 0.8f},
							 {(float)159/255, (float)159/255, (float)251/255, 0.8f} };

static float *getNextRangeColor(int &range_color_current){
	if(range_color_current >= range_color_count)
		range_color_current = 0;

	return range_colors[range_color_current];
}

void drawPlaceHolder(const LWCustomObjAccess *access, Vector3 position, float size){
	Vector3 xUp(size, 0.0, 0.0), xDown(-(size), 0.0, 0.0);
	Vector3 yUp(0.0, size, 0.0), yDown(0.0,-(size), 0.0);
	Vector3 zUp(0.0, 0.0, size), zDown(0.0, 0.0,-(size));

	xUp   = position +  xUp;
	xDown = position +  xDown;

	yUp   = position +  yUp;
	yDown = position +  yDown;

	zUp   = position +  zUp;
	zDown = position +  zDown;
	
	double _xu[3], _xd[3], _yu[3], _yd[3], _zu[3], _zd[3];

	_xu[0] = xUp.x;
	_xu[1] = xUp.y;
	_xu[2] = xUp.z;

	_xd[0] = xDown.x;
	_xd[1] = xDown.y;
	_xd[2] = xDown.z;

	_yu[0] = yUp.x;
	_yu[1] = yUp.y;
	_yu[2] = yUp.z;

	_yd[0] = yDown.x;
	_yd[1] = yDown.y;
	_yd[2] = yDown.z;

	_zu[0] = zUp.x;
	_zu[1] = zUp.y;
	_zu[2] = zUp.z;

	_zd[0] = zDown.x;
	_zd[1] = zDown.y;
	_zd[2] = zDown.z;

	access->setColor(access->dispData, colors[0]);

	access->line(access->dispData, _xd, _xu, LWCSYS_OBJECT);
	access->line(access->dispData, _yd, _yu, LWCSYS_OBJECT);
	access->line(access->dispData, _zd, _zu, LWCSYS_OBJECT);
}


void drawTempMesh(const LWCustomObjAccess *access, TempMesh tmesh, Vector3 position){

	for(int i=0; i < tmesh.polygons.size(); i++){
		double3 *verts = new double3[tmesh.polygons.at(i).size()];

		for(int j=0; j < tmesh.polygons.at(i).size(); j++){
				
			verts[j][0] = tmesh.polygons.at(i).at(j).x + position.x;
			verts[j][1] = tmesh.polygons.at(i).at(j).y + position.y;
			verts[j][2] = tmesh.polygons.at(i).at(j).z + position.z;
		}

		access->setColor(access->dispData, getNextRangeColor(color_counter));
		access->polygon(access->dispData, (unsigned int)tmesh.polygons.at(i).size(), verts,  LWCSYS_OBJECT);

		access->setColor(access->dispData, colors[0]);
		for(int j=0; j < tmesh.polygons.at(i).size()-1; j++){
			access->line(access->dispData, verts[j], verts[j+1], LWCSYS_OBJECT);
		}
	}
}
/*
======================================================================
Create()

Handler callback.  Allocate and initialize instance data.  We don't
really have any instance data, but we need to return something, and
this at least shows what create() would normally be doing.
====================================================================== */

XCALL_( static LWInstance )
cloneVisualizerCreate( void *priv, LWItemID item, LWError *err ){
   MyObject *inst;

   if ( (inst = (MyObject *)malloc( sizeof( MyObject )))) {
      inst->id = item;
   }
   else
      *err = "Couldn't allocate 4 bytes!";

   return inst;
}


/*
======================================================================
Destroy()

Handler callback.  Free resources allocated by Create().
====================================================================== */

XCALL_( static void )
cloneVisualizerDestroy( MyObject *inst )
{
   if( inst ) free( inst );
}


/*
======================================================================
Copy()

Handler callback.  Copy instance data.
====================================================================== */

XCALL_( static LWError )
cloneVisualizerCopy( MyObject *to, MyObject *from )
{
   LWItemID id;

   id = to->id;
   *to = *from;
   to->id = id;

   return NULL;
}


/*
======================================================================
Load(), Save(), Describe(), UseItems(), ChangeID(), Init(), Cleanup(),
NewTime(), Flags()

We're a pretty simple plug-in, so we don't need to do anything in
these callbacks, but they're here if we want to fill them in later.
====================================================================== */

XCALL_( static LWError )
cloneVisualizerLoad( MyObject *inst, const LWLoadState *ls ) { return NULL; }

XCALL_( static LWError )
cloneVisualizerSave( MyObject *inst, const LWSaveState *ss ) { return NULL; }

XCALL_( static const char * )
cloneVisualizerDescribe( MyObject *inst ) { return "Deep Clone Visualizer."; }

XCALL_( static const LWItemID * )
cloneVisualizerUseItems( MyObject *inst ) { return NULL; }

XCALL_( static void )
cloneVisualizerChangeID( MyObject *inst, const LWItemID *ids ) { }

XCALL_( static LWError )
cloneVisualizerInit( MyObject *inst, int mode ) { return NULL; }

XCALL_( static void )
cloneVisualizerCleanup( MyObject *inst ) { }

XCALL_( static LWError )
cloneVisualizerNewTime( MyObject *inst, LWFrame fr, LWTime t ) { return NULL; }

XCALL_( static unsigned int )
cloneVisualizerFlags( MyObject *inst ) { return 0; }


/*
======================================================================
Evaluate()

Handler callback.  This is called each time the custom object needs to
be redrawn.  We just draw our edges, letting Layout choose the color
based on selection state and user preference.
====================================================================== */

XCALL_( static void )cloneVisualizerEvaluate( MyObject *inst, const LWCustomObjAccess *access ){
	
	access->setDrawMode( access->dispData, LWDRAWMODE_DEPTHTEST | LWDRAWMODE_DEPTHWRITE | LWDRAWMODE_CULLFACE );
	
	DeepCloneFX::clonerItem = inst->id;
	color_counter = -1;

	if(DeepCloneFX::objectToClones.size() > 0){
		
		for(Vector3 pos: *DeepCloneFX::points){
			++color_counter;
			drawTempMesh(access, DeepCloneFX::objectMeshInfo[0], pos);
		}
	}else{
		for(Vector3 pos: *DeepCloneFX::points){
			drawPlaceHolder(access, pos, 0.2f);
		}
	}
	
}


/*
======================================================================
Handler()

Handler activation function.  Check the version, get some globals, and
fill in the callback fields of the handler structure.
====================================================================== */

XCALL_( static int )DeepCloneVisualizer( int version, GlobalFunc *global, LWCustomObjHandler *local, void *serverData){
   if ( version != LWCUSTOMOBJ_VERSION )
      return AFUNC_BADVERSION;

   _globalVisualizer = global;

   local->inst->create  = cloneVisualizerCreate;
   local->inst->destroy = (void (*)(LWInstance)) cloneVisualizerDestroy;
   local->inst->load    = (LWError (*)(LWInstance, const LWLoadState *))cloneVisualizerLoad;
   local->inst->save    = (LWError (*)(LWInstance, const LWSaveState *))cloneVisualizerSave;
   local->inst->copy    = (LWError (*)(LWInstance, const LWInstance ))cloneVisualizerCopy;
   local->inst->descln  = (const char *(*)(LWInstance))cloneVisualizerDescribe;

   if ( local->item ) {
      local->item->useItems = (const LWItemID *(*)(LWInstance))cloneVisualizerUseItems;
	  local->item->changeID = (void (*)(LWInstance, const LWItemID *))cloneVisualizerChangeID;
   }

   if ( local->rend ) {
	  local->rend->init    = (LWError (*)(LWInstance, int))cloneVisualizerInit;
      local->rend->cleanup = (void (*)(LWInstance))cloneVisualizerCleanup;
	  local->rend->newTime = (LWError (*)(LWInstance, LWFrame, LWTime))cloneVisualizerNewTime;
   }

   local->evaluate = (void (*)(LWInstance, const LWCustomObjAccess *))cloneVisualizerEvaluate;
   local->flags    = (unsigned int (*)(LWInstance))cloneVisualizerFlags;

   return AFUNC_OK;
}

