/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "HelixPointsNode.h"


HelixPointsNode::HelixPointsNode(){
	out_Points.reset(new vector<Point3D>);   
}

void HelixPointsNode::evaluate(){
	if(*in_NumberOfPoints > 0){
		out_Points->clear(); 
	
		float ratio = 1;
		if(*in_ArcAngle > 0)
			ratio = *in_ArcAngle/360;
	
		for(int i=0; i <= *in_NumberOfPoints * ratio; i++){

			float angle = 2.0f*(float)X_PI*i/(*in_NumberOfPoints);
			float x = cos(angle)*(*in_Radius);
			float y = sin(angle)*(*in_Radius);
			float z = angle/(*in_Rise);
		
			Point3D newPoint(x,y,z);
			out_Points->push_back(newPoint);

			/*if(axis == CIRCLE_X_AXIS){
				points.push_back(Vector3(0.0f, y, x));
			}else if(axis == CIRCLE_Y_AXIS){
				points.push_back(Vector3(x, 0.0f, y));
			}else{
				points.push_back(Vector3(x, y, 0.0f));
			}*/
		
		}
	}
}
