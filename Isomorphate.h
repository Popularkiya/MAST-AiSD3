#pragma once
#include <iostream>
#include "Tree.h"

#define NUM_OF_LEAFS 10
#define ERROR -2

class Isomorphate {
private:
	int** isomorphic_array;
	int x, y;
	int Connect(Leaf* leaf, int* connection_tab, int how_many_conn_nums, bool rev);
	int NodeHandler(Leaf* nodeFirst, Leaf* nodeSecond);
	int SonsAsNode(int son, int node);
	int NodeAsSon(int node, int son);
	int BruteForce(Leaf* nodeFirst, Leaf* nodeSecond);

public:
	Isomorphate(Tree* First, Tree* Second);
	int GetFromArray(int y, int x);
	void PutToArray(int y, int x, int value);
	void PrintArray();
	void DestroyArray();
	~Isomorphate();
};
