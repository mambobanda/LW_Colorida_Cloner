/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "BrickPointsNode.h"

BrickPointsNode::BrickPointsNode(){
	out_Points.reset(new vector<Point3D>);   
}

void BrickPointsNode::evaluate(){
	if(*in_NumberOfPoints > 0){
		out_Points->clear(); 

		float spacing    = 0.0f;
		float rowSpacing = 0.0f;
		float rowOffset  = 0.0f;

		for(int r=0; r < *in_Rows; r++){
			for(int i=0; i < *in_NumberOfPoints; i++){
				Point3D newPoint;

				newPoint.x = 0.0f + spacing + rowOffset;
				newPoint.y = 0.0f + rowSpacing;
				newPoint.z = 0.0f;

				spacing += *in_Spacing;

				out_Points->push_back(newPoint);
			}

			spacing = 0.0f;

			if(((r+2)%2) == 0){
				rowOffset = *in_RowOffset;
			}else{
				rowOffset = 0;
			}

			rowSpacing += *in_RowSpacing;
		}
	}
}