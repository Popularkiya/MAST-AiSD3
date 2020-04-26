#include "Tree.h"
#include "Leaf.h"
#include "FIFO.h"


Tree::Tree(){
	int relationship=NULL;
	this->amount_of_nodes = 0;
	Leaf* add_ptr=nullptr;
	Leaf* parent = nullptr;
	char number[2] = {NULL,NULL}, *end, input;
	int i = 0;
	while (true) {
		input = _getchar_nolock();
		if (input == ';') { break; }
		else if (number[0] != NULL && (input == '(' || input == ')' || input == ',')) {
			char* num_tab = (char*)malloc(i * sizeof(char));
			if (num_tab != NULL) {
				for (int j = 0; j < i; j++) {
					num_tab[j] = number[j];
				}
				int value = strtol(num_tab, &end, 10);
				Leaf* tmp = new Leaf(parent, value);
				if (relationship == CHILD) {
					add_ptr->SetChild(tmp);
					add_ptr = add_ptr->Child();
				}
				else if (relationship == BROTHER) {
					add_ptr->SetBrother(tmp);
					add_ptr = add_ptr->Brother();
				}
				free(num_tab);
				for (int j = 0; j < i; j++) {
					number[j] = NULL;
				}
				i = 0;
			}
			else {
				std::cout << "memory not granted" << std::endl;
			}
		}

		if (input == '(') {
			this->amount_of_nodes++;
			if (parent == nullptr) {
				add_ptr = new Leaf();
				this->nodes_tab = new Leaf * [1];
				nodes_tab[0] = add_ptr;
			}
			else {
				Leaf* tmp = new Leaf(parent);
				if (relationship == CHILD) {
					add_ptr->SetChild(tmp);
					add_ptr = add_ptr->Child();
				}
				else if (relationship == BROTHER) {
					add_ptr->SetBrother(tmp);
					add_ptr = add_ptr->Brother();
				}
				//add_ptr = new Leaf(parent);
			}
			parent = add_ptr;
			relationship = CHILD;
			//add_ptr = add_ptr->Child();
		}
		else if (input == ',') {
			relationship = BROTHER;
			//add_ptr = add_ptr->Brother();
		}
		else if (input == ')') {
			add_ptr = add_ptr->Parent();
			parent = add_ptr->Parent();
		}
		else {
			if (i < 2) {
				number[i++] = input;
			}
		}
	}
}



int Tree::SearchLeaf(Leaf* node, int sought){
	FIFO* queue = new FIFO(node);
	int result = this->Search(sought, queue);
	delete queue;
	return result;
}



int Tree::Search(int sought, FIFO* queue) {
	int found;
	Leaf* ptr = queue->Remove();
	if (ptr != NULL) {
		if (ptr->Value() == sought) { return FOUND; }
		else {
			if (ptr->Child() != nullptr) {
				queue->Add(ptr->Child());
				Leaf* bro = ptr->Child()->Brother();
				while (bro != nullptr) {
					queue->Add(bro);
					bro = bro->Brother();
				}
			}
			found = Search(sought, queue);
			return found;
		}
	}
	else { return NOT_FOUND; }
}



int Tree::AmountOfNodes() {
	return this->amount_of_nodes;
}



void Tree::TagNodes(){
	FIFO* queue = new FIFO(nodes_tab[0]);
	Tag(queue);
	delete queue;
}



void Tree::Tag(FIFO* queue) {
	static int count = A;
	Leaf* ptr = queue->Remove();
	if (ptr != NULL) {
		if (ptr->Child() != nullptr) {
			ptr->SetValue(count++);
			Leaf** extended_node_tab = new Leaf * [count - A];
			for (int i = 0; i < count - A -1; i++) {
				extended_node_tab[i] = this->nodes_tab[i];
			}
			extended_node_tab[count - A - 1] = ptr;
			delete this->nodes_tab;
			this->nodes_tab = nullptr;
			this->nodes_tab = extended_node_tab;
			queue->Add(ptr->Child());
			Leaf* bro = ptr->Child()->Brother();
			while (bro != nullptr) {
				queue->Add(bro);
				bro = bro->Brother();
			}
		}
		this->Tag(queue);
	}
}


Leaf* Tree::ReturnNodesPtr(int node){
	return this->nodes_tab[node - A];
}

void Tree::DeleteBranches() {
	for (int i = this->amount_of_nodes - 1; i >= 0; i--) {
		Leaf* node = this->nodes_tab[i] ;
		Leaf* deleted = node->Child();
		while (deleted != nullptr) {
			Leaf* next_child = deleted->Brother();
			delete deleted;
			deleted = next_child;
		}
	}
	delete this->nodes_tab[0];
	nodes_tab[0] = nullptr;
	delete this->nodes_tab;
	nodes_tab = nullptr;
}

Tree::~Tree(){
	this->DeleteBranches();
}