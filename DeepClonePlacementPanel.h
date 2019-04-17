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
#include <lwxpanel.h>            
#include <lwhost.h>  

///void valueUpdateNotifyFunc(LWXPanelID pan, unsigned int cid, unsigned int vid, int event_type);

class PlacementPanel{
private:
	static GlobalFunc *_global;
	static LWXPanelFuncs* mc_xpanf;
	
	static void valueUpdateNotifyFunc(LWXPanelID pan, unsigned int cid, unsigned int vid, int event_type);
	static void finalizeCloneFunc(LWXPanelID pan, int cid);

public:
	static LWXPanelID panel;
	static LWXPanelID drawLinearPlacementView(GlobalFunc _global, LWXPanelFuncs* mc_xpanf);
};