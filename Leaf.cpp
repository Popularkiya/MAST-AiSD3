#include "Leaf.h"


Leaf::Leaf() {
	this->value = ROOT;
	this->parent = nullptr;
	this->brother = nullptr;
	this->child = nullptr;
}



Leaf::Leaf(Leaf* parent) {
	this->value = NODE;
	this->parent = parent;
	this->brother = nullptr;
	this->child = nullptr;
}



Leaf::Leaf(Leaf* parent, int value) {
	this->value = value;
	this->parent = parent;
	this->brother = nullptr;
	this->child = nullptr;
}



int Leaf::Value() {
	return this->value;
}


void Leaf::SetValue(int value) {
	this->value = value;
}



void Leaf::SetBrother(Leaf* brother){
	this->brother = brother;
}



void Leaf::SetChild(Leaf* child){
	this->child = child;
}



Leaf* Leaf::Brother() {
	return this->brother;
}



Leaf* Leaf::Child() {
	return this->child;
}



Leaf* Leaf::Parent() {
	return this->parent;
}

Leaf::~Leaf() {}