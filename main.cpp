#include <iostream>
#include "Leaf.h"
#include "Tree.h"
#include "Isomorphate.h"
#include "FIFO.h"

int main() {
	Tree** Tree_array;
	int n,score;
	scanf("%d ", &n);
	Tree_array = new Tree * [n];
	for (int i = 0; i < n; i++) {
		Tree_array[i] = new Tree();
		Tree_array[i]->TagNodes();
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			Isomorphate* max_aggrement = new Isomorphate(Tree_array[i],Tree_array[j]);
			score=max_aggrement->GetFromArray(A, A);
			printf("%d\n", NUM_OF_LEAFS-score);
			//max_aggrement->PrintArray();
			delete max_aggrement;
			max_aggrement = nullptr;
		}
	}
	for (int i = 0; i < n; i++) {
		delete Tree_array[i];
		Tree_array[i] = nullptr;
	}
	delete[] Tree_array;
	

	return 0;
}