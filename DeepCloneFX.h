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

#include "lwrender.h"
#include "xTypes.h"
#include "Common.h"


class DeepCloneFX{
public:
	static LWItemID clonerItem;
	static vector<LWItemID> objectToClones;
	static vector<TempMesh> objectMeshInfo;
	static xPointArray points;

	static void finalizeClone();
	static void initSystem();
	static void initSystem2();

	static void close();

	static int  validSfSceneObject(GlobalFunc *_glSceneFunctions, LWItemID itemid);
	static int addSelectedObject();
};