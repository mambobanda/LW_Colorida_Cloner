/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include "xNode.h"

unsigned int xNode::id_base = 0x001;


bool xNode::hasEvaluated(){
    return evaluated;
}

xNode::xNode(){
    xNodeID = ++id_base;
    evaluated = false;
}

void xNode::evaluateUp(){
    for(xNode *parent: parents){
        if(!parent->hasEvaluated()){
            parent->evaluateUp();
        }
    }
    
    this->evaluate();
    
    evaluated = true;
}

void xNode::evaluateNode(){
    for(xNode *parent: parents){
        if(!parent->hasEvaluated()){
            parent->evaluateUp();
        }
    }
    
    this->evaluate();
    
    for(xNode *child: children){
        child->evaluateNode();
    }
    
    evaluated = true;
}

unsigned int xNode::getNodeID(){
    return xNodeID;
}

void xNode::addParent(xNode *parent){
    parents.push_back(parent);
}

