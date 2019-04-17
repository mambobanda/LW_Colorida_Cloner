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


#include <vector>

using namespace std;


class xNode{
protected:
    static unsigned int id_base;
    
    int _typeid;
    unsigned int xNodeID;

    vector<xNode *>parents;
    vector<xNode *> children;
    
    bool evaluated;
    virtual void evaluate() = 0;
public:
    xNode();
    template<typename T> void connect(xNode *, T &, T &);
    void addParent(xNode *);
    unsigned int getNodeID();
    bool hasEvaluated();   
    void evaluateNode();
    void evaluateUp();
};

template<typename T>
void xNode::connect(xNode *child, T &from, T &to){
    for(xNode *n: children){
        if(n->getNodeID() == child->getNodeID()){
            to = from;          
            return;
        }
    }
    
    children.push_back(child);
    to = from;
    child->addParent(this);
}