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

#include "xNode.h"
#include "xTypes.h"

class GridPointsNode: public xNode{
public:
	xVector  in_NumberOfPoints;
	xVector  in_Spacing;
	xFloat   in_RandomPositionOffSet;
	xFloat   in_RandomScaleOffSet;
	xFloat   in_RandomRotationOffSet;

	xPointArray out_Points;

	GridPointsNode();
	void evaluate();
};