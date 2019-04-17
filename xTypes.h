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


#include <memory>
#include <vector>
#include "vector.h"

using namespace std;

typedef shared_ptr<int>    xInteger;
typedef shared_ptr<float>  xFloat;
typedef shared_ptr<double> xDouble;
typedef shared_ptr<bool>   xBoolean;
typedef shared_ptr<Vector3> xVector;
typedef shared_ptr<vector<Point3D>> xPointArray;