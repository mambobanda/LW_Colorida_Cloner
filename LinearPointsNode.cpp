/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "LinearPointsNode.h"

LinearPointsNode::LinearPointsNode(){
	out_Points.reset(new vector<Point3D>);   
}

void LinearPointsNode::evaluate(){
	if(*in_NumberOfPoints > 0){
		out_Points->clear(); 

		float coffx = 0.0f;
		float coffy = 0.0f;
		float coffz = 0.0f;

		for(int i=0; i < *in_NumberOfPoints; i++){
			Point3D newPoint;

			newPoint.x = 0.0f + coffx;
			newPoint.y = 0.0f + coffy;
			newPoint.z = 0.0f + coffz;

			coffx += in_OffSet->x;
			coffy += in_OffSet->y;
			coffz += in_OffSet->z;

			out_Points->push_back(newPoint);
		}
	}
}