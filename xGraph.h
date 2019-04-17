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

class xGraph{
private:
    vector<xNode*> nodes;
public:
    void addNode(xNode* node);
    void evaluateGraph();
};