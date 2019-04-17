/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "xGraph.h"

void xGraph::addNode(xNode *node){
    nodes.push_back(node);
}



void xGraph::evaluateGraph(){
    if(nodes.size() > 0){
        xNode *root = nodes[0];
        root->evaluateNode();
    }    
}