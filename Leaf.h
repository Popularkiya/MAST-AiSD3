#pragma once
#include <iostream>

#define ROOT 0
#define NODE -1

class Leaf {
private:
	int value;
	Leaf* parent;
	Leaf* brother;
	Leaf* child;

public:
	Leaf();//root
	Leaf(Leaf* parent);//node
	Leaf(Leaf* parent, int value);//leaf
	int Value();
	void SetValue(int value);
	void SetBrother(Leaf* brother);
	void SetChild(Leaf* child);
	Leaf* Brother();
	Leaf* Child();
	Leaf* Parent();
	~Leaf();
};