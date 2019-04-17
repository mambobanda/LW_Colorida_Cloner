/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "GridPointsNode.h"
#include <algorithm>
#include <limits>
#include <random>
#include <ctime>

GridPointsNode::GridPointsNode(){
	out_Points.reset(new vector<Point3D>);   
}

void GridPointsNode::evaluate(){
	std::time_t time = std::time(nullptr);
	std::uniform_real_distribution<> distPos(0.0f, *in_RandomPositionOffSet);
	unsigned int k = 10;
	/*std::uniform_real_distribution<> distScale(0.0f, *in_RandomPositionOffSet);
	std::uniform_real_distribution<> distRot(0.0f, *in_RandomPositionOffSet);*/

	if( in_NumberOfPoints->x > 0.0f ||
		in_NumberOfPoints->y > 0.0f ||
		in_NumberOfPoints->z > 0.0f ){

		out_Points->clear(); 

		int xcount = (int)in_NumberOfPoints->x;
		int ycount = (int)in_NumberOfPoints->y;
		int zcount = (int)in_NumberOfPoints->z;

		float xspacing = 0.0f;
		float yspacing = 0.0f;
		float zspacing = 0.0f;

		for(int x=0; x < xcount; x++){
			for(int y=0; y < ycount; y++){
				for(int z=0; z < zcount; z++){
					std::default_random_engine genx((++k)*(unsigned int)time);
					std::default_random_engine geny((++k)*(unsigned int)time);
					std::default_random_engine genz((++k)*(unsigned int)time);
					
					float posx = (float)distPos(genx);
					float posy = (float)distPos(geny);
					float posz = (float)distPos(genz);

					Point3D newPoint;

					newPoint.x = xspacing + posx;
					newPoint.y = yspacing + posy;
					newPoint.z = zspacing + posz;

					out_Points->push_back(newPoint);

					zspacing += in_Spacing->z;
				}

				zspacing = 0.0f;
				yspacing += in_Spacing->y;
			}

			zspacing = 0.0f;
			yspacing = 0.0f;
			xspacing += in_Spacing->x;
		}

	}
}