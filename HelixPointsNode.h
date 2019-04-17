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

class HelixPointsNode: public xNode{
public:
	xInteger in_NumberOfPoints;
	xFloat   in_ArcAngle;
	xFloat   in_Radius;
	xFloat   in_Rise;

	xPointArray out_Points;

	HelixPointsNode();
	void evaluate();
};