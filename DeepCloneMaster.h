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


#include <lwrender.h>
#include "BrickPointsNode.h"
#include "LinearPointsNode.h"
#include "CircularPointsNode.h"
#include "GridPointsNode.h"
#include "HelixPointsNode.h"
#include "ConstantNode.h"

class DeepCloneMasterGraph{
public:
////Application Globals///////////////////////////////
	static GlobalFunc *_global;	

	static void initialize(){
		LinearPlacementGraph::initialize();
		CircularPlacementGraph::initialize();
		BrickPlacementGraph::initialize();
		GridPlacementGraph::initialize();
		HelixPlacementGraph::initialize();
	}

///Linear Placement//////////////////////////////////
	class LinearPlacementGraph{
	public:
		static bool initialized;
		static ConstantNode<int>   pointCount;
		static ConstantNode<Vector3> offset; 
		static LinearPointsNode linearPoints;		 

		static void initialize(){
			if(initialized) return;

			*pointCount.out_value = 5;
			*offset.out_value = Vector3(1.0f, 0.0f, 0.0f); 

			pointCount.connect(&linearPoints, pointCount.out_value, linearPoints.in_NumberOfPoints);
			offset.connect(&linearPoints, offset.out_value, linearPoints.in_OffSet);

			linearPoints.evaluateNode();

			initialized = true;
		}
	};

///Circular Placement///////////////////////////////
	class CircularPlacementGraph{
	public:
		static bool initialized;
		static ConstantNode<int>  axis;
		static ConstantNode<int>  pointCount;
		static ConstantNode<int>  ringCount;
		static ConstantNode<float> arcAngle;
		static ConstantNode<float> radius;
		static ConstantNode<float> radiusOffset;
		static ConstantNode<Vector3> ringOffset;
		static CircularPointsNode circularPoints;	

		static void initialize(){
			if(initialized) return;

			*pointCount.out_value = 360;
			*radius.out_value = 10.0f;
			*axis.out_value   = 1;
			*arcAngle.out_value = 360;
			*ringCount.out_value = 1;
			*radiusOffset.out_value = 1;

			axis.connect(&circularPoints, axis.out_value, circularPoints.in_Axis);
			ringCount.connect(&circularPoints, ringCount.out_value, circularPoints.in_NumberOfRings);
			arcAngle.connect(&circularPoints, arcAngle.out_value, circularPoints.in_ArcAngle);
			pointCount.connect(&circularPoints, pointCount.out_value, circularPoints.in_NumberOfPoints);
			radius.connect(&circularPoints, radius.out_value, circularPoints.in_Radius);
			radiusOffset.connect(&circularPoints, radiusOffset.out_value, circularPoints.in_RadiusOffset);

			circularPoints.evaluateNode();

			initialized = true;
		}
	};

///Brick Placement////////////////////////////////////////////////
	class BrickPlacementGraph{
	public:
		static bool initialized;
		
		static ConstantNode<int>  pointCount;
		static ConstantNode<int>  rows;
		static ConstantNode<float> rowsSpacing;
		static ConstantNode<float> rowOffset;
		static ConstantNode<float> spacing; 
		static BrickPointsNode brickPoints;

		static void initialize(){
			if(initialized) return;

			*pointCount.out_value = 10;
			*rows.out_value = 5;
			*rowsSpacing.out_value = 1.2f;
			*rowOffset.out_value = 0.5f;
			*spacing.out_value = 1;

			pointCount.connect(&brickPoints, pointCount.out_value, brickPoints.in_NumberOfPoints);
			rows.connect(&brickPoints, rows.out_value, brickPoints.in_Rows);
			rowsSpacing.connect(&brickPoints, rowsSpacing.out_value, brickPoints.in_RowSpacing);
			rowOffset.connect(&brickPoints, rowOffset.out_value, brickPoints.in_RowOffset);
			spacing.connect(&brickPoints, spacing.out_value, brickPoints.in_Spacing);

			brickPoints.evaluateNode();

			initialized = true;
		}
	};

///Grid Placement//////////////////////////////////
	class GridPlacementGraph{
	public:
		static bool initialized;

		static ConstantNode<Vector3> pointCount;
		static ConstantNode<Vector3> spacing;
		static ConstantNode<float> randomPositionOffset; 
		static ConstantNode<float> randomScaleOffset; 
		static ConstantNode<float> randomRotationOffset; 

		static GridPointsNode gridPoints;		 

		static void initialize(){
			if(initialized) return;

			*pointCount.out_value = Vector3(5.0f, 5.0f, 5.0f);

			*spacing.out_value = Vector3(1.0f, 1.0f, 1.0f);;

			*randomPositionOffset.out_value = 0.0;
			*randomScaleOffset.out_value    = 0.0;
			*randomRotationOffset.out_value = 0.0;

			pointCount.connect(&gridPoints, pointCount.out_value, gridPoints.in_NumberOfPoints);
			spacing.connect(&gridPoints, spacing.out_value, gridPoints.in_Spacing);
			randomPositionOffset.connect(&gridPoints, randomPositionOffset.out_value, gridPoints.in_RandomPositionOffSet);
			randomScaleOffset.connect(&gridPoints, randomScaleOffset.out_value, gridPoints.in_RandomScaleOffSet);
			randomRotationOffset.connect(&gridPoints, randomRotationOffset.out_value, gridPoints.in_RandomRotationOffSet);
			
			gridPoints.evaluateNode();

			initialized = true;
		}
	};

///Helix Placement//////////////////////////////////
	class HelixPlacementGraph{
	public:
		static bool initialized;

		static ConstantNode<int> pointCount;
		static ConstantNode<float> arcAngle; 
		static ConstantNode<float> radius;
		static ConstantNode<float> rise; 

		static HelixPointsNode helixPoints;		 

		static void initialize(){
			if(initialized) return;

			*pointCount.out_value = 20;

			*arcAngle.out_value = 720.0;

			*radius.out_value = 2.0f;

			*rise.out_value = 2.0f;

			pointCount.connect(&helixPoints, pointCount.out_value, helixPoints.in_NumberOfPoints);
			arcAngle.connect(&helixPoints, arcAngle.out_value, helixPoints.in_ArcAngle);
			radius.connect(&helixPoints, radius.out_value, helixPoints.in_Radius);
			rise.connect(&helixPoints, rise.out_value, helixPoints.in_Rise);
			
			helixPoints.evaluateNode();

			initialized = true;
		}
	};
};