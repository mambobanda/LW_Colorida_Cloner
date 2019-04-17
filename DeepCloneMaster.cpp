/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "DeepCloneMaster.h"

//Master Graph Initialize///////////////////////////////////////////////
GlobalFunc *DeepCloneMasterGraph::_global = NULL;

//Linear Placement Initialize/////////////////////////////////////////////
bool DeepCloneMasterGraph::LinearPlacementGraph::initialized = false;
ConstantNode<int>   DeepCloneMasterGraph::LinearPlacementGraph::pointCount;
ConstantNode<Vector3> DeepCloneMasterGraph::LinearPlacementGraph::offset;  
LinearPointsNode DeepCloneMasterGraph::LinearPlacementGraph::linearPoints;

//Circular Placement Initialize///////////////////////////////////////////
bool DeepCloneMasterGraph::CircularPlacementGraph::initialized = false;
ConstantNode<int>  DeepCloneMasterGraph::CircularPlacementGraph::axis;
ConstantNode<float>  DeepCloneMasterGraph::CircularPlacementGraph::arcAngle;
ConstantNode<int>  DeepCloneMasterGraph::CircularPlacementGraph::pointCount;
ConstantNode<float> DeepCloneMasterGraph::CircularPlacementGraph::radius;
ConstantNode<float> DeepCloneMasterGraph::CircularPlacementGraph::radiusOffset;
ConstantNode<int> DeepCloneMasterGraph::CircularPlacementGraph::ringCount;
CircularPointsNode DeepCloneMasterGraph::CircularPlacementGraph::circularPoints;

//Brick Placement Initialize//////////////////////////////////////////////
bool DeepCloneMasterGraph::BrickPlacementGraph::initialized = false;
ConstantNode<int>  DeepCloneMasterGraph::BrickPlacementGraph::pointCount;
ConstantNode<int>  DeepCloneMasterGraph::BrickPlacementGraph::rows;
ConstantNode<float> DeepCloneMasterGraph::BrickPlacementGraph::rowsSpacing;
ConstantNode<float> DeepCloneMasterGraph::BrickPlacementGraph::rowOffset;
ConstantNode<float> DeepCloneMasterGraph::BrickPlacementGraph::spacing; 
BrickPointsNode DeepCloneMasterGraph::BrickPlacementGraph::brickPoints;

//Grid Placement Initialize//////////////////////////////////////////////
bool DeepCloneMasterGraph::GridPlacementGraph::initialized = false;
ConstantNode<Vector3>   DeepCloneMasterGraph::GridPlacementGraph::pointCount;
ConstantNode<Vector3> DeepCloneMasterGraph::GridPlacementGraph::spacing; 
ConstantNode<float> DeepCloneMasterGraph::GridPlacementGraph::randomPositionOffset; 
ConstantNode<float> DeepCloneMasterGraph::GridPlacementGraph::randomRotationOffset;
ConstantNode<float> DeepCloneMasterGraph::GridPlacementGraph::randomScaleOffset; 
GridPointsNode      DeepCloneMasterGraph::GridPlacementGraph::gridPoints;

//Helix Placement Initialize/////////////////////////////////////////////
bool DeepCloneMasterGraph::HelixPlacementGraph::initialized = false;
ConstantNode<int>   DeepCloneMasterGraph::HelixPlacementGraph::pointCount;
ConstantNode<float> DeepCloneMasterGraph::HelixPlacementGraph::radius;
ConstantNode<float> DeepCloneMasterGraph::HelixPlacementGraph::rise;
ConstantNode<float> DeepCloneMasterGraph::HelixPlacementGraph::arcAngle;
HelixPointsNode DeepCloneMasterGraph::HelixPlacementGraph::helixPoints;