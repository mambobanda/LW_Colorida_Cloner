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

class BrickPointsNode: public xNode{
public:
	xInteger in_NumberOfPoints;
	xInteger in_Rows;
	xFloat   in_RowSpacing;
	xFloat   in_RowOffset;
	xVector  in_InitialPosition;
	xFloat   in_Spacing;

	xPointArray out_Points;

	BrickPointsNode();
	void evaluate();
};