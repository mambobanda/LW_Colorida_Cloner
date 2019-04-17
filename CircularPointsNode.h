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


#include "Common.h"
#include "xNode.h"
#include "xTypes.h"

#define CIRCLE_X_AXIS 0
#define CIRCLE_Y_AXIS 1
#define CIRCLE_Z_AXIS 2

class CircularPointsNode: public xNode{
private:
	vector<Vector3> makeCircle(int segments, float arcangle, float radius, int axis);
public:

	xInteger in_Axis;
	xInteger in_NumberOfPoints;
	xInteger in_NumberOfRings;
	xFloat   in_ArcAngle;
	xFloat   in_Radius;
	xFloat   in_RadiusOffset;
	xVector  in_InitialPosition;
	xVector  in_RingOffset;

	xPointArray out_Points;

	CircularPointsNode();
	void evaluate();
};