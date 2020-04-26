#pragma once
# include <iostream>
#include "Leaf.h"

struct fifo {
	Leaf* current;
	fifo* next;
};

class FIFO {
private:
	fifo* start;
	fifo* end;

public:
	FIFO(Leaf* first);
	void Add(Leaf* value);
	Leaf* Remove();
	~FIFO();
};