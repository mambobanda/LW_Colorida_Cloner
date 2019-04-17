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

#include <vector>
#include <lwserver.h>
#include <lwhandler.h>
#include <lwrender.h>
#include <lwcustobj.h>
#include <lwhost.h>
#include "Vector.h"

using namespace std;

#define X_PI 3.14159265359

typedef double double3[3];

typedef struct{
	vector<vector<Vector3 > > polygons;	
}TempMesh;

typedef struct {
   LWItemID    id;
   GlobalFunc  *global;
} MyObject;

typedef struct{
	LWPolID *pols;
	int counter;
}PolyIDS;

size_t polScan(void *data, LWPolID pol);
TempMesh buildTempMesh(LWItemID itemid, GlobalFunc *_global);