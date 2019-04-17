/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "Common.h"

size_t polScan(void *data, LWPolID pol){
	PolyIDS *dat = (PolyIDS*)data;
	dat->pols[dat->counter] = pol;
	dat->counter++;

	return 0;
}

TempMesh buildTempMesh(LWItemID itemid, GlobalFunc *_global){
	LWObjectInfo *objinfo   = (LWObjectInfo *)_global( LWOBJECTINFO_GLOBAL, GFUSE_TRANSIENT );
	LWMeshInfo   *meshinfo  = objinfo->meshInfo(itemid, 0);

	TempMesh tmesh;
	
	PolyIDS *ids = new PolyIDS;
	ids->pols    = new LWPolID[meshinfo->numPolygons(meshinfo)];
	ids->counter = 0;
	meshinfo->scanPolys(meshinfo, polScan, ids);

	for(int i=0; i < meshinfo->numPolygons(meshinfo); i++){

		vector<Vector3> poly;

		for(int j=0; j < meshinfo->polSize(meshinfo, ids->pols[i]); j++){
			LWFVector vert;
			LWPntID pnt = meshinfo->polVertex(meshinfo, ids->pols[i], j);

			meshinfo->pntOtherPos(meshinfo, pnt, vert);

			poly.push_back(Vector3(vert[0], vert[1], vert[2]));
		}

		tmesh.polygons.push_back(poly);
	}

	delete[] ids->pols;
	delete  ids;

	return tmesh;
}