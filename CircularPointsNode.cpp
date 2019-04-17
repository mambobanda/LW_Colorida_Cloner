/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "CircularPointsNode.h"


CircularPointsNode::CircularPointsNode(){
	out_Points.reset(new vector<Point3D>);   
}

vector<Vector3> CircularPointsNode::makeCircle(int segments, float arcangle, float radius, int axis){
	vector<Vector3> points;
	float ratio = 1.0f;

	if(arcangle > 0)
		ratio = arcangle/360.0f;
	
	for(int i=0; i <= segments*ratio; i++){
		float angle = 2.0f*(float)X_PI*i/segments;
		float x = cos(angle)*radius;
		float y = sin(angle)*radius;
		
		if(axis == CIRCLE_X_AXIS){
			points.push_back(Vector3(0.0f, y, x));
		}else if(axis == CIRCLE_Y_AXIS){
			points.push_back(Vector3(x, 0.0f, y));
		}else{
			points.push_back(Vector3(x, y, 0.0f));
		}
		
	}

	return points;
}

void CircularPointsNode::evaluate(){
	if(*in_NumberOfPoints > 0){
		out_Points->clear(); 

		float in_RadiusOffsetCounter = 0;
		Vector3 posOffset(0.0f, 0.0f, 0.0f);

		for(int i=0; i < *in_NumberOfRings; i++){
			xPointArray temp(new vector<Point3D>); 
			*temp = makeCircle(*in_NumberOfPoints, *in_ArcAngle, *in_Radius + in_RadiusOffsetCounter, *in_Axis);
			
			out_Points->insert(out_Points->end(),  temp->begin(), temp->end());
			in_RadiusOffsetCounter += *in_RadiusOffset;
		}
	}
}