#include "Isomorphate.h"



Isomorphate::Isomorphate(Tree* First, Tree* Second) {
	this->y = First->AmountOfNodes() + NUM_OF_LEAFS;
	this->x = Second->AmountOfNodes() + NUM_OF_LEAFS;
	this->isomorphic_array = (int**)malloc(this->y * sizeof(int*));
	if (this->isomorphic_array != NULL) {
		for (int i = 0; i < this->y; i++) {
			this->isomorphic_array[i] = (int*)malloc(this->x * sizeof(int));
			if (this->isomorphic_array[i] == NULL) {
				std::cout << "memory not granted!" << std::endl;
			}
			else {
				for (int j = 0; j < this->x; j++) {
					this->isomorphic_array[i][j] = 0;
					//leaf with leaf-----------------------------------------------------------------
					if (i <= 10 && j <= 10 && i == j) {
						this->isomorphic_array[i][j] = 1;
					}
					//leaf A with node B-------------------------------------------------------------
					else if (j >= A && i <= 10) {
						Leaf* node = Second->ReturnNodesPtr(j);
						this->isomorphic_array[i][j] = Second->SearchLeaf(node, i);
					}
					//node A with leaf A-------------------------------------------------------------
					else if (i >= A && j <= 10) {
						Leaf* node = First->ReturnNodesPtr(i);
						this->isomorphic_array[i][j] = First->SearchLeaf(node, j);
					}
				}
			}
		}
		//node with node-------------------------------------------------------------------------
		for (int i = First->AmountOfNodes() + A-1; i >= A; i--) {
			for (int j = Second->AmountOfNodes() + A-1; j >= A; j--) {
				Leaf* first_node = First->ReturnNodesPtr(i);
				Leaf* second_node = Second->ReturnNodesPtr(j);
				this->isomorphic_array[i][j] = this->NodeHandler(first_node, second_node);
			}
		}
	}
	else
		std::cout << "memory not granted!" << std::endl;
}



int Isomorphate::NodeHandler(Leaf* nodeFirst, Leaf* nodeSecond) {
	int best_option = 0;
	int outcome = 0;

	// node as node------------------------------------------------
	outcome = this->BruteForce(nodeFirst, nodeSecond);
	if (outcome > best_option) {
		best_option = outcome;
	}

	//node as son--------------------------------------------------
	Leaf* ptr = nodeSecond->Child();
	while (ptr != nullptr) {
		outcome = this->NodeAsSon(nodeFirst->Value(),ptr->Value());
		if (outcome > best_option) {
			best_option = outcome;
		}
		ptr = ptr->Brother();
	}

	//son as node--------------------------------------------------
	ptr = nodeFirst->Child();
	while (ptr != nullptr) {
		outcome = this->SonsAsNode(ptr->Value(),nodeSecond->Value());
		if (outcome > best_option) {
			best_option = outcome;
		}
		ptr = ptr->Brother();
	}

	return best_option;
}



int Isomorphate::SonsAsNode(int son, int node){
	return this->isomorphic_array[son][node];
}



int Isomorphate::NodeAsSon(int node, int son){
	return this->isomorphic_array[node][son];
}



int Isomorphate::BruteForce(Leaf* nodeFirst, Leaf* nodeSecond){
	int first_children_num = 0, second_children_num = 0;
	Leaf* ptr = nodeFirst->Child();
	while (ptr!= nullptr) { 
		first_children_num++;
		ptr = ptr->Brother();
	}
	ptr = nodeSecond->Child();
	while (ptr!= nullptr) {
		second_children_num++;
		ptr = ptr->Brother();
	}
	bool rev = false;
	int how_many_connection_nums=0;
	int* connection_tab = NULL;
	Leaf* node = nullptr;
	//-----------------------------------------------------------------
	if (first_children_num > second_children_num) {
		connection_tab = (int*)malloc(first_children_num * sizeof(int));
		how_many_connection_nums = first_children_num;
		rev = true;
		node = nodeSecond;
	}
	else {
		connection_tab = (int*)malloc(second_children_num * sizeof(int));
		how_many_connection_nums = second_children_num;
		node = nodeFirst;
	}
	//------------------------------------------------------------------
	if (connection_tab != NULL) {
		ptr = node->Child();
		for (int i = 0; i < how_many_connection_nums; i++) {
			connection_tab[i] = ptr->Value();
			ptr = ptr->Brother();
		}
		return this->Connect(node->Child(), connection_tab, how_many_connection_nums,rev);
	}
	else {
		std::cout << "memory not granted" << std::endl;
		return ERROR;
	}
}



int Isomorphate::Connect(Leaf* leaf, int* connection_tab, int how_many_conn_nums,bool rev){
	int static best_score = 0;
	int static current_score = 0;
	int static recursion_lvl = 0;
	if (leaf == nullptr) {
		if (current_score > best_score) { best_score = current_score; }
		return 0;
	}
	else {
		for (int i = 0; i < how_many_conn_nums; i++) {
			int tmp = connection_tab[i];
			if (connection_tab[i] != 0) {
				if (rev != true) {
					current_score += this->isomorphic_array[leaf->Value()][connection_tab[i]];
				}
				else {
					current_score += this->isomorphic_array[connection_tab[i]][leaf->Value()];
				}
				connection_tab[i] = 0;
				recursion_lvl++;
				current_score += this->Connect(leaf->Brother(), connection_tab, how_many_conn_nums,rev);
				recursion_lvl--;
				if (recursion_lvl == 0) {
					current_score = 0;
				}
			}
			connection_tab[i] = tmp;
		}
		if (recursion_lvl == 0) {
			return best_score;
		}
	}
}



int Isomorphate::GetFromArray(int y, int x){
	return this->isomorphic_array[y-1][x-1];
}



void Isomorphate::PutToArray(int y, int x, int value){
	this->isomorphic_array[y-1][x-1] = value;
}



void Isomorphate::DestroyArray(){
	for (int i = 0; i < this->y; i++) {
		free(this->isomorphic_array[y]);
	}
	free(this->isomorphic_array);
}



Isomorphate::~Isomorphate() {
	this->DestroyArray();
}