#include "FIFO.h"

FIFO::FIFO(Leaf* first){
	this->start = (fifo*)malloc(sizeof(fifo));
	if (this->start != NULL) {
		this->start->current = first;
		this->start->next = nullptr;
		this->end = this->start;
	}
	else {
		std::cout << "broken FIFO constructor" << std::endl;
	}
}



void FIFO::Add(Leaf* value){
	fifo* added = (fifo*)malloc(sizeof(fifo));
	if (added != NULL) {
		added->current = value;
		added->next = nullptr;
		if (this->start == nullptr) {
			this->start = added;
			this->end = this->start;
		}
		else {
			this->end->next = added;
			this->end = this->end->next;
		}
	}
	else {
		std::cout << "broken FIFO.Add()" << std::endl;
	}
}



Leaf* FIFO::Remove(){
	if (this->start == nullptr) { return NULL; }
	else {
		Leaf* tmp = this->start->current;
		fifo* removed = this->start;
		this->start = this->start->next;
		free(removed);
		return tmp;
	}
}



FIFO::~FIFO(){
	if (this->start != nullptr) {
		while (this->start != nullptr) {
			this->Remove();
		}
	}
}