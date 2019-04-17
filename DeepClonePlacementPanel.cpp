/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "LightwaveCommon.h"
#include "DeepCloneFX.h"
#include "DeepCloneMaster.h"
#include "DeepClonePlacementPanel.h"

GlobalFunc *PlacementPanel::_global = NULL;
LWXPanelFuncs* PlacementPanel::mc_xpanf = NULL;
LWXPanelID PlacementPanel::panel;

enum {
	PLACEMENT_TYPE=0x8100, PLACEMENT_STACK, PLACEMENT_TYPE_LIST, CLONE_BUTTON,
	
	LINEAR_PLACEMENT_GROUP, LINEAR_PLACEMENT_POINT_COUNT, LINEAR_PLACEMENT_POINT_OFFSET,

	CIRCULAR_PLACEMENT_GROUP, CIRCULAR_PLACEMENT_AXIS, CIRCULAR_PLACEMENT_POINT_COUNT, CIRCULAR_PLACEMENT_RADIUS,
	CIRCULAR_PLACEMENT_RADIUS_OFFSET, CIRCULAR_PLACEMENT_DEGREE, CIRCULAR_PLACEMENT_CIRCLES, CIRCULAR_PLACEMENT_OFFSET,

	BRICK_PLACEMENT_GROUP, BRICK_PLACEMENT_POINT_COUNT, BRICK_PLACEMENT_ROWS, BRICK_PLACEMENT_ROW_SPACING,
	BRICK_PLACEMENT_ROW_OFFSET, BRICK_PLACEMENT_SPACING,

	GRID_PLACEMENT_GROUP, GRID_PLACEMENT_POINT_COUNT_X, GRID_PLACEMENT_POINT_COUNT_Y, GRID_PLACEMENT_POINT_COUNT_Z, 
	GRID_PLACEMENT_SPACING_X, GRID_PLACEMENT_SPACING_Y,  GRID_PLACEMENT_SPACING_Z, GRID_PLACEMENT_RANDOM_POSITION, GRID_PLACEMENT_RANDOM_SCALE, GRID_PLACEMENT_RANDOM_ROTATION,

	HELIX_PLACEMENT_GROUP, HELIX_PLACEMENT_ARC_ANGLE, HELIX_PLACEMENT_POINT_COUNT, HELIX_PLACEMENT_RADIUS, HELIX_PLACEMENT_RISE, 
};

static char *placementTypeChoice[] = {
   "Linear",
   "Circular",
   "Brick",
   "Grid",
   "Helix",
   NULL
};

static LWXPanelControl ctrl_list[] = {
	{CLONE_BUTTON, "Clone Object", "vButton" },
	{PLACEMENT_TYPE, "Placement Type ", "iPopChoice"},

	{LINEAR_PLACEMENT_POINT_COUNT, "Number Of Clones:", "integer" },
	{LINEAR_PLACEMENT_POINT_OFFSET, "Offset:",  "float3" },

	{CIRCULAR_PLACEMENT_AXIS, "Arc Angle:", "axis" },
	{CIRCULAR_PLACEMENT_CIRCLES, "Circles:", "integer" },
	{CIRCULAR_PLACEMENT_POINT_COUNT, "Number Of Clones Per Circle:", "integer" },
	{CIRCULAR_PLACEMENT_RADIUS, "Radius:", "float" },
	{CIRCULAR_PLACEMENT_RADIUS_OFFSET, "Radius Offset:", "float" },
	{CIRCULAR_PLACEMENT_DEGREE, "Arc Angle:", "float" },
	//{CIRCULAR_PLACEMENT_OFFSET, "Circle Offset:",  "float3" },

	{BRICK_PLACEMENT_POINT_COUNT, "Number Of Clones:", "integer" },
	{BRICK_PLACEMENT_SPACING, "Spacing:", "float" },
	{BRICK_PLACEMENT_ROWS, "Rows:", "integer" },
	{BRICK_PLACEMENT_ROW_SPACING, "Row Spacing:", "float" },
	{BRICK_PLACEMENT_ROW_OFFSET, "Row Offset:", "float" },

	{GRID_PLACEMENT_POINT_COUNT_X, "Total Count X:", "integer"},
	{GRID_PLACEMENT_POINT_COUNT_Y, "Y:", "integer"},
	{GRID_PLACEMENT_POINT_COUNT_Z, "Z:", "integer"},
	{GRID_PLACEMENT_SPACING_X, "Spacing X:", "float"},
	{GRID_PLACEMENT_SPACING_Y, "Y:", "float"},
	{GRID_PLACEMENT_SPACING_Z, "Z:", "float"},
	{GRID_PLACEMENT_RANDOM_POSITION, "Randomise Position:", "float"},

	{HELIX_PLACEMENT_POINT_COUNT, "Number of Clones Per Arc:", "integer"},
	{HELIX_PLACEMENT_ARC_ANGLE, "Arc Angle:", "float"},
	{HELIX_PLACEMENT_RADIUS, "Radius:", "float"},
	{HELIX_PLACEMENT_RISE, "Rise:", "float"},

	{ 0 }
};

static LWXPanelDataDesc data_desc[] = {
	{PLACEMENT_TYPE,  "Placement Type ", "integer"},

	{LINEAR_PLACEMENT_POINT_COUNT,  "Number Of Clones:", "integer" },
    {LINEAR_PLACEMENT_POINT_OFFSET, "Offset:",  "float3" },

	{CIRCULAR_PLACEMENT_AXIS, "Arc Angle:", "integer" },
	{CIRCULAR_PLACEMENT_CIRCLES, "Circles:", "integer" },
	{CIRCULAR_PLACEMENT_POINT_COUNT, "Number Of Clones Per Circle:", "integer" },
	{CIRCULAR_PLACEMENT_RADIUS, "Radius:", "float" },
	{CIRCULAR_PLACEMENT_RADIUS_OFFSET, "Radius Offset:", "float" },
	{CIRCULAR_PLACEMENT_DEGREE, "Arc Angle:", "float" },
	//{CIRCULAR_PLACEMENT_OFFSET, "Circle Offset:",  "float3" },

	{BRICK_PLACEMENT_POINT_COUNT, "Number Of Clones:", "integer" },
	{BRICK_PLACEMENT_SPACING, "Spacing:", "float" },
	{BRICK_PLACEMENT_ROWS, "Rows:", "integer" },
	{BRICK_PLACEMENT_ROW_SPACING, "Row Spacing:", "float" },
	{BRICK_PLACEMENT_ROW_OFFSET, "Row Offset:", "float" },

	{GRID_PLACEMENT_POINT_COUNT_X, "Total Count X:", "integer"},
	{GRID_PLACEMENT_POINT_COUNT_Y, "Y:", "integer"},
	{GRID_PLACEMENT_POINT_COUNT_Z, "Z:", "integer"},
	{GRID_PLACEMENT_SPACING_X, "Spacing Count X:", "float"},
	{GRID_PLACEMENT_SPACING_Y, "Y:", "float"},
	{GRID_PLACEMENT_SPACING_Z, "Z:", "float"},
	{GRID_PLACEMENT_RANDOM_POSITION, "Randomise Position:", "float"},
	
	{HELIX_PLACEMENT_POINT_COUNT, "Number of Clones Per Arc:",  "integer"},
	{HELIX_PLACEMENT_ARC_ANGLE, "Arc Angle:", "float"},
	{HELIX_PLACEMENT_RADIUS, "Radius:", "float"},
	{HELIX_PLACEMENT_RISE, "Rise:", "float"},

	{ 0 }
};

LWXPanelID PlacementPanel::drawLinearPlacementView(GlobalFunc _g, LWXPanelFuncs* mcx){
	
	_global  = _g;
	mc_xpanf = mcx;

	LWXPanelHint hint[] = {

		XpMIN(LINEAR_PLACEMENT_POINT_COUNT, 0),
		XpSTEP(LINEAR_PLACEMENT_POINT_OFFSET, 1),
		
		XpMIN(CIRCULAR_PLACEMENT_POINT_COUNT, 3),
		XpMIN(CIRCULAR_PLACEMENT_RADIUS, 0),
		XpMIN(CIRCULAR_PLACEMENT_RADIUS_OFFSET, 0),
		XpMIN(CIRCULAR_PLACEMENT_CIRCLES, 1),
		XpMIN(CIRCULAR_PLACEMENT_RADIUS_OFFSET, 0),
		XpMIN(CIRCULAR_PLACEMENT_DEGREE, 0),
		XpMAX(CIRCULAR_PLACEMENT_DEGREE, 360),
		
		XpMIN(BRICK_PLACEMENT_POINT_COUNT, 0),
		XpMIN(BRICK_PLACEMENT_SPACING, 0),
		XpMIN(BRICK_PLACEMENT_ROWS, 1),
		XpMIN(BRICK_PLACEMENT_ROW_SPACING, 0),
		XpSTEP(BRICK_PLACEMENT_ROW_OFFSET, 1),

		XpMIN(GRID_PLACEMENT_POINT_COUNT_X, 1),
		XpMIN(GRID_PLACEMENT_POINT_COUNT_Y, 1),
		XpMIN(GRID_PLACEMENT_POINT_COUNT_Z, 1),
		XpMIN(GRID_PLACEMENT_SPACING_X, 0),
		XpMIN(GRID_PLACEMENT_SPACING_Y, 0),
		XpMIN(GRID_PLACEMENT_SPACING_Z, 0),
		XpMIN(GRID_PLACEMENT_RANDOM_POSITION, 0),
		
		XpMIN(HELIX_PLACEMENT_POINT_COUNT, 1),
		XpMIN(HELIX_PLACEMENT_ARC_ANGLE, 1),
		XpMIN(HELIX_PLACEMENT_RADIUS, 1),
		XpMIN(HELIX_PLACEMENT_RISE, 1),

		XpGROUP_(LINEAR_PLACEMENT_GROUP),
			XpH(LINEAR_PLACEMENT_POINT_COUNT),
			XpH(LINEAR_PLACEMENT_POINT_OFFSET),
			XpH(0),
		XpLABEL(LINEAR_PLACEMENT_GROUP, "Linear Placement"),

		XpGROUP_(CIRCULAR_PLACEMENT_GROUP),
			XpH(CIRCULAR_PLACEMENT_AXIS),
			XpH(CIRCULAR_PLACEMENT_CIRCLES),
			XpH(CIRCULAR_PLACEMENT_POINT_COUNT),
			XpH(CIRCULAR_PLACEMENT_DEGREE),
			XpH(CIRCULAR_PLACEMENT_RADIUS),
			XpH(CIRCULAR_PLACEMENT_RADIUS_OFFSET),
			//XpH(CIRCULAR_PLACEMENT_OFFSET),
			XpH(0),
		XpLABEL(CIRCULAR_PLACEMENT_GROUP, "Circular Placement"),

		XpGROUP_(BRICK_PLACEMENT_GROUP),
			XpH(BRICK_PLACEMENT_POINT_COUNT),
			XpH(BRICK_PLACEMENT_SPACING),
			XpH(BRICK_PLACEMENT_ROWS),
			XpH(BRICK_PLACEMENT_ROW_SPACING),
			XpH(BRICK_PLACEMENT_ROW_OFFSET),
			XpH(0),
		XpLABEL(BRICK_PLACEMENT_GROUP, "Brick Placement"),

		XpGROUP_(GRID_PLACEMENT_GROUP),
			XpH(GRID_PLACEMENT_POINT_COUNT_X),
			XpH(GRID_PLACEMENT_POINT_COUNT_Y),
			XpH(GRID_PLACEMENT_POINT_COUNT_Z),
			XpH(GRID_PLACEMENT_SPACING_X),
			XpH(GRID_PLACEMENT_SPACING_Y),
			XpH(GRID_PLACEMENT_SPACING_Z),
			XpH(GRID_PLACEMENT_RANDOM_POSITION),
			//XpH(GRID_PLACEMENT_RANDOM_ROTATION),
			//XpH(GRID_PLACEMENT_RANDOM_SCALE),
			XpH(0),
		XpLABEL(GRID_PLACEMENT_GROUP, "Grid Placement"),

		XpGROUP_(HELIX_PLACEMENT_GROUP),
			XpH(HELIX_PLACEMENT_POINT_COUNT),
			XpH(HELIX_PLACEMENT_ARC_ANGLE),
			XpH(HELIX_PLACEMENT_RADIUS),
			XpH(HELIX_PLACEMENT_RISE),
			XpH(0),
		XpLABEL(HELIX_PLACEMENT_GROUP, "Helix Placement"),

		XpSTACK_(PLACEMENT_STACK, PLACEMENT_TYPE),
			XpH( LINEAR_PLACEMENT_GROUP),
			XpH( CIRCULAR_PLACEMENT_GROUP),
			XpH( BRICK_PLACEMENT_GROUP),
			XpH( GRID_PLACEMENT_GROUP),
			XpH( HELIX_PLACEMENT_GROUP),
			XpH(0),

		XpSTRLIST(PLACEMENT_TYPE, placementTypeChoice),

		XpCHGNOTIFY(valueUpdateNotifyFunc),
		//XpBUTNOTIFY(finalizeCloneFunc, CLONE_BUTTON ),

		XpDIVADD_(PLACEMENT_TYPE),
		XpDIVADD_(CLONE_BUTTON),
		XpDIVADD_(CIRCULAR_PLACEMENT_AXIS),
		XpDIVADD_(LINEAR_PLACEMENT_POINT_COUNT),
		
		XpDIVADD_(CIRCULAR_PLACEMENT_DEGREE),
		XpDIVADD_(CIRCULAR_PLACEMENT_POINT_COUNT),
		XpDIVADD_(CIRCULAR_PLACEMENT_RADIUS),
		XpDIVADD_(CIRCULAR_PLACEMENT_RADIUS_OFFSET),

		XpDIVADD_(BRICK_PLACEMENT_POINT_COUNT),
		XpDIVADD_(BRICK_PLACEMENT_SPACING),

		XpDIVADD_(GRID_PLACEMENT_POINT_COUNT_Z),
		XpDIVADD_(GRID_PLACEMENT_SPACING_Z),
		XpDIVADD_(GRID_PLACEMENT_RANDOM_POSITION),
		XpDIVADD_(GRID_PLACEMENT_RANDOM_SCALE),
		XpDIVADD_(GRID_PLACEMENT_RANDOM_ROTATION),

		XpDIVADD_(HELIX_PLACEMENT_POINT_COUNT),
		XpDIVADD_(HELIX_PLACEMENT_ARC_ANGLE),
		XpDIVADD_(HELIX_PLACEMENT_RADIUS),
		XpDIVADD_(HELIX_PLACEMENT_RISE),

		XpEND
	};

	panel = mc_xpanf->create(LWXP_FORM, ctrl_list );
	mc_xpanf->describe(panel, data_desc, NULL, NULL);
    mc_xpanf->hint(panel,0,hint);

	double offset[3];
	offset[0] = DeepCloneMasterGraph::LinearPlacementGraph::offset.out_value->x;
	offset[1] = DeepCloneMasterGraph::LinearPlacementGraph::offset.out_value->y;
	offset[2] = DeepCloneMasterGraph::LinearPlacementGraph::offset.out_value->z;

	FSETINT(mc_xpanf, panel, PLACEMENT_TYPE, 0);

	//Linear/////////
	FSETINT(mc_xpanf, panel, LINEAR_PLACEMENT_POINT_COUNT, *DeepCloneMasterGraph::LinearPlacementGraph::pointCount.out_value);
	mc_xpanf->formSet(panel, LINEAR_PLACEMENT_POINT_OFFSET, offset);

	//Circular///////
	FSETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_AXIS, *DeepCloneMasterGraph::CircularPlacementGraph::axis.out_value);
	FSETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_CIRCLES, *DeepCloneMasterGraph::CircularPlacementGraph::ringCount.out_value);
	FSETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_POINT_COUNT, *DeepCloneMasterGraph::CircularPlacementGraph::pointCount.out_value);
	FSETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_RADIUS, *DeepCloneMasterGraph::CircularPlacementGraph::radius.out_value);
	FSETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_RADIUS_OFFSET, *DeepCloneMasterGraph::CircularPlacementGraph::radiusOffset.out_value);
	FSETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_DEGREE, *DeepCloneMasterGraph::CircularPlacementGraph::arcAngle.out_value);

	//Brick/////////
	FSETINT(mc_xpanf, panel, BRICK_PLACEMENT_POINT_COUNT, *DeepCloneMasterGraph::BrickPlacementGraph::pointCount.out_value);
	FSETINT(mc_xpanf, panel, BRICK_PLACEMENT_ROWS, *DeepCloneMasterGraph::BrickPlacementGraph::rows.out_value);
	FSETFLT(mc_xpanf, panel, BRICK_PLACEMENT_ROW_SPACING, *DeepCloneMasterGraph::BrickPlacementGraph::rowsSpacing.out_value);
	FSETFLT(mc_xpanf, panel, BRICK_PLACEMENT_ROW_OFFSET, *DeepCloneMasterGraph::BrickPlacementGraph::rowOffset.out_value);
	FSETFLT(mc_xpanf, panel, BRICK_PLACEMENT_SPACING, *DeepCloneMasterGraph::BrickPlacementGraph::spacing.out_value);

	//Grid//////////
	FSETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_X, (int)DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->x);
	FSETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_Y, (int)DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->y);
	FSETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_Z, (int)DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->z);
	FSETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_X, DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->x);
	FSETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_Y, DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->y);
	FSETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_Z, DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->z);
	FSETFLT(mc_xpanf, panel, GRID_PLACEMENT_RANDOM_POSITION, *DeepCloneMasterGraph::GridPlacementGraph::randomPositionOffset.out_value);

	//Helix/////////
	FSETINT(mc_xpanf, panel, HELIX_PLACEMENT_POINT_COUNT, *DeepCloneMasterGraph::HelixPlacementGraph::pointCount.out_value);
	FSETFLT(mc_xpanf, panel, HELIX_PLACEMENT_ARC_ANGLE, *DeepCloneMasterGraph::HelixPlacementGraph::arcAngle.out_value);
	FSETFLT(mc_xpanf, panel, HELIX_PLACEMENT_RADIUS, *DeepCloneMasterGraph::HelixPlacementGraph::radius.out_value);
	FSETFLT(mc_xpanf, panel, HELIX_PLACEMENT_RISE, *DeepCloneMasterGraph::HelixPlacementGraph::rise.out_value);

	return panel;
}


void PlacementPanel::valueUpdateNotifyFunc(LWXPanelID pan, unsigned int cid, unsigned int vid, int event_type){
	LWCommandFunc *evaluate = ( LWCommandFunc *)_global( LWCOMMANDFUNC_GLOBAL, GFUSE_TRANSIENT );
	
	switch (cid){
	case CLONE_BUTTON:
		{
			DeepCloneFX::finalizeClone();
			DeepCloneFX::close();
		}
	case PLACEMENT_TYPE:
		{
			int newval = FGETINT(mc_xpanf, panel, PLACEMENT_TYPE);

			if(newval == 0){
				DeepCloneFX::points = DeepCloneMasterGraph::LinearPlacementGraph::linearPoints.out_Points;
			}else if(newval == 1){
				DeepCloneFX::points = DeepCloneMasterGraph::CircularPlacementGraph::circularPoints.out_Points;
			}else if(newval == 2){
				DeepCloneFX::points = DeepCloneMasterGraph::BrickPlacementGraph::brickPoints.out_Points;
			}else if(newval == 3){
				DeepCloneFX::points = DeepCloneMasterGraph::GridPlacementGraph::gridPoints.out_Points;
			}else if(newval == 4){
				DeepCloneFX::points = DeepCloneMasterGraph::HelixPlacementGraph::helixPoints.out_Points;
			}

			evaluate("RedrawNow");
			break;
		}
	case LINEAR_PLACEMENT_POINT_COUNT:
		{
			int newval = FGETINT(mc_xpanf, panel, LINEAR_PLACEMENT_POINT_COUNT);
			*DeepCloneMasterGraph::LinearPlacementGraph::pointCount.out_value = newval;
			DeepCloneMasterGraph::LinearPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case LINEAR_PLACEMENT_POINT_OFFSET:
		{
			double *newval;
			newval = (double*)mc_xpanf->formGet(panel, LINEAR_PLACEMENT_POINT_OFFSET);
			*DeepCloneMasterGraph::LinearPlacementGraph::offset.out_value = Vector3((float)newval[0], (float)newval[1], (float)newval[2]);
			DeepCloneMasterGraph::LinearPlacementGraph::offset.evaluateNode();

			evaluate("RedrawNow");

			break;
		}	
	case CIRCULAR_PLACEMENT_POINT_COUNT:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_POINT_COUNT);
			*DeepCloneMasterGraph::CircularPlacementGraph::pointCount.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}	
	case CIRCULAR_PLACEMENT_RADIUS:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_RADIUS);
			*DeepCloneMasterGraph::CircularPlacementGraph::radius.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::radius.evaluateNode();

			evaluate("RedrawNow");

			break;
		}	
	case CIRCULAR_PLACEMENT_AXIS:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_AXIS);
			*DeepCloneMasterGraph::CircularPlacementGraph::axis.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::axis.evaluateNode();

			evaluate("RedrawNow");

			break;
		}	
	case CIRCULAR_PLACEMENT_DEGREE:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_DEGREE);
			*DeepCloneMasterGraph::CircularPlacementGraph::arcAngle.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::arcAngle.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case CIRCULAR_PLACEMENT_CIRCLES:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, CIRCULAR_PLACEMENT_CIRCLES);
			*DeepCloneMasterGraph::CircularPlacementGraph::ringCount.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::ringCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case CIRCULAR_PLACEMENT_RADIUS_OFFSET:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, CIRCULAR_PLACEMENT_RADIUS_OFFSET);
			*DeepCloneMasterGraph::CircularPlacementGraph::radiusOffset.out_value = newval;
			DeepCloneMasterGraph::CircularPlacementGraph::radiusOffset.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case BRICK_PLACEMENT_POINT_COUNT:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, BRICK_PLACEMENT_POINT_COUNT);
			*DeepCloneMasterGraph::BrickPlacementGraph::pointCount.out_value = newval;
			 DeepCloneMasterGraph::BrickPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case BRICK_PLACEMENT_ROWS:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, BRICK_PLACEMENT_ROWS);
			*DeepCloneMasterGraph::BrickPlacementGraph::rows.out_value = newval;
			 DeepCloneMasterGraph::BrickPlacementGraph::rows.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case BRICK_PLACEMENT_SPACING:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, BRICK_PLACEMENT_SPACING);
			*DeepCloneMasterGraph::BrickPlacementGraph::spacing.out_value = newval;
			 DeepCloneMasterGraph::BrickPlacementGraph::spacing.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case BRICK_PLACEMENT_ROW_OFFSET:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, BRICK_PLACEMENT_ROW_OFFSET);
			*DeepCloneMasterGraph::BrickPlacementGraph::rowOffset.out_value = newval;
			DeepCloneMasterGraph::BrickPlacementGraph::rowOffset.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case BRICK_PLACEMENT_ROW_SPACING:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, BRICK_PLACEMENT_ROW_SPACING);
			*DeepCloneMasterGraph::BrickPlacementGraph::rowsSpacing.out_value = newval;
			DeepCloneMasterGraph::BrickPlacementGraph::rowsSpacing.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_POINT_COUNT_X:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_X);
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->x = (float)newval;
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_POINT_COUNT_Y:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_Y);
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->y = (float)newval;
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_POINT_COUNT_Z:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, GRID_PLACEMENT_POINT_COUNT_Z);
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.out_value->z = (float)newval;
			DeepCloneMasterGraph::GridPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_SPACING_X:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_X);
			DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->x = newval;
			DeepCloneMasterGraph::GridPlacementGraph::spacing.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_SPACING_Y:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_Y);
			DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->y = newval;
			DeepCloneMasterGraph::GridPlacementGraph::spacing.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_SPACING_Z:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, GRID_PLACEMENT_SPACING_Z);
			DeepCloneMasterGraph::GridPlacementGraph::spacing.out_value->z = newval;
			DeepCloneMasterGraph::GridPlacementGraph::spacing.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case GRID_PLACEMENT_RANDOM_POSITION:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, GRID_PLACEMENT_RANDOM_POSITION);
			*DeepCloneMasterGraph::GridPlacementGraph::randomPositionOffset.out_value = newval;
			DeepCloneMasterGraph::GridPlacementGraph::randomPositionOffset.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case HELIX_PLACEMENT_POINT_COUNT:
		{
			int newval;
			newval = FGETINT(mc_xpanf, panel, HELIX_PLACEMENT_POINT_COUNT);
			*DeepCloneMasterGraph::HelixPlacementGraph::pointCount.out_value = newval;
			DeepCloneMasterGraph::HelixPlacementGraph::pointCount.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case HELIX_PLACEMENT_ARC_ANGLE:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, HELIX_PLACEMENT_ARC_ANGLE);
			*DeepCloneMasterGraph::HelixPlacementGraph::arcAngle.out_value = newval;
			DeepCloneMasterGraph::HelixPlacementGraph::arcAngle.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case HELIX_PLACEMENT_RADIUS:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, HELIX_PLACEMENT_RADIUS);
			*DeepCloneMasterGraph::HelixPlacementGraph::radius.out_value = newval;
			DeepCloneMasterGraph::HelixPlacementGraph::radius.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	case HELIX_PLACEMENT_RISE:
		{
			float newval;
			newval = (float)FGETFLT(mc_xpanf, panel, HELIX_PLACEMENT_RISE);
			*DeepCloneMasterGraph::HelixPlacementGraph::rise.out_value = newval;
			DeepCloneMasterGraph::HelixPlacementGraph::rise.evaluateNode();

			evaluate("RedrawNow");

			break;
		}
	default:
		break;
	}
}