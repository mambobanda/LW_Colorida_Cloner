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


#include <lwserver.h>
#include <lwrender.h>
#include "xNode.h"
#include "xTypes.h"

class AddNullNode: public xNode{
private:
	GlobalFunc *_global;
	bool       isReady;
public:
	xPointArray in_Positions;

	void setGlobal( GlobalFunc *global );
	AddNullNode();
	void evaluate();
};