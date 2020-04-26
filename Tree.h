#pragma once
#include <iostream>
#include "Leaf.h"
#include "FIFO.h"

#define FOUND 1
#define NOT_FOUND 0

#define A 11
#define B 12
#define C 13
#define D 14
#define E 15
#define F 16
#define G 17 
#define H 18
#define I 19
#define J 20

#define PARENT -10
#define BROTHER -11
#define CHILD -12

class Tree {

private:
	Leaf** nodes_tab;
	int amount_of_nodes;
	void Tag(FIFO* queue);
	int Search(int sought, FIFO* queue);
public:
	Tree();
	int SearchLeaf(Leaf* node, int sought);
	int AmountOfNodes();
	void TagNodes();
	void DeleteBranches();
	Leaf* ReturnNodesPtr(int node);
	~Tree();
};