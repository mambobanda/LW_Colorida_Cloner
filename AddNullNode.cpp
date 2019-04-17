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
#include "DeepCloneFX.h"
#include "LightwaveCommon.h"
#include "AddNullNode.h"

AddNullNode::AddNullNode(){
	isReady = false;
}

void AddNullNode::setGlobal( GlobalFunc *global ){
	_global = global;
}

void AddNullNode::evaluate(){

	if(!isReady){
		LWCommandFunc *evaluate  = (LWCommandFunc *)_global( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
		LWInterfaceInfo *intinfo = (LWInterfaceInfo *)_global( LWINTERFACEINFO_GLOBAL, GFUSE_TRANSIENT );

		char eval[200];
		
		sprintf_s(eval, sizeof(eval), "AddNull _DeepCloneNull_");
		evaluate(eval);

		DeepCloneFX::points = in_Positions;

		sprintf_s(eval, sizeof(eval), "ApplyServer CustomObjHandler DeepClone_Clone_Visualizer");
		evaluate(eval);

		isReady = true;
	}
	
}