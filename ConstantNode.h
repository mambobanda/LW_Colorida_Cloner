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
#include <memory>
#include "xNode.h"
#include "xTypes.h"

template<typename T>
class ConstantNode: public xNode{

public:
	shared_ptr<T> out_value;

	ConstantNode();
	void evaluate();
};

template<typename T>
ConstantNode<T>::ConstantNode(){
	out_value.reset(new T());
}

template<typename T>
void ConstantNode<T>::evaluate(){
	
}