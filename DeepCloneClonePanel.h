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
#include <lwgeneric.h>
#include <lwrender.h>
#include <lwpanel.h>
#include <lwxpanel.h>
#include <lwhost.h>
#include <lwdisplay.h>

class ClonePanel{
private:
	static GlobalFunc  *_global;
	static LWPanelFuncs* panf;
	static LWPanelID   panel;

	static LWControl *mode;
	static LWControl *sequenceType;
	static LWControl *edit;
	static LWControl *objectList;

	static int  objectListCount( void *data );
	static char *objectListName( void *data, int index );

	static int validSfSceneObject(GlobalFunc *_glSceneFunctions, LWItemID itemid);
	static void addSelectedObject();
	static void groupEditOptionsEvent( LWControl *control, void *data);

public:
	static int tabPosX;
	static int tabPosY;

	static void drawObjectView(GlobalFunc _global, LWPanelFuncs* panf, LWPanelID panel);
	static void clearObjectView();
};