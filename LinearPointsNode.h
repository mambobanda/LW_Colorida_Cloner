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

class LinearPointsNode: public xNode{
public:
	xInteger in_NumberOfPoints;
	xVector  in_InitialPosition;
	xVector  in_OffSet;

	xPointArray out_Points;

	LinearPointsNode();
	void evaluate();
};