#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include "Node.hpp"
#include "Node.cpp"
#include "DynArr.hpp"
#include <functional>
void subFunction() {
	Node * root = new Node(9);
	Node* root2 = new Node(15);
	root = root->heapify(11);
	root = root->heapify(10);
	root = root->heapify(12);
	root = root->heapify(23);
	root = root->heapify(14);
	/*if (!root->isOk()) throw "Exception";
	root2 = root2->heapify(17);
	root2 = root2->heapify(7);
	root2 = root2->heapify(19);
	root = root->merge(root, root2);*/
	root = root->remove(10);
	if (!root->isOk()) throw "Exception";
	std::cout << std::endl;
}
DynArr<float>* doHeapSort(float* tab, int tabSize) {
	DynArr<float>* tmpTab = new DynArr<float>(tabSize);
	Node* root = new Node(tab[0]);
	for (int i = 1; i < tabSize; i++) {
		root = root->heapify(tab[i]);
	}
	int index = 0;
	while (root) {
		tmpTab->Set(index,root->getMin());
		root = root->deleteMin();
		index++;
	}
	return tmpTab;
}
void heapSort() {
	float tf[5] = { 1.0,15.0,-1.0,25.0, 6.0 };
	DynArr<float>* tab = doHeapSort(tf, 5);
	tab->push_back(1000.0);
	for (int i = 0; i < 6; i++) {
		std::cout << tab->Get(i) << " ";
	}
	std::cout << std::endl;
}
void append() {
	float tf[5] = { 1.0,15.0,-1.0,25.0, 6.0 };
	float tf2[5] = { 2.0,16.0,0.0,26.0, 7.0 };
	DynArr<float>* tab = doHeapSort(tf, 5);
	DynArr<float>* tab2 = doHeapSort(tf2, 5);
	tab->append(*tab2);
	tab->Reverse();
	tab->push_back(204);
	std::function<void(float)> affiche = [](float elem) {
		printf("%f ", elem);
	};
	tab->iter(affiche);

	/*for (int i = 0; i < 11; i++) {
		std::cout << tab->Get(i) << " ";
	}*/
	std::cout << std::endl;
}
int main() {
	//subFunction();
	//heapSort();
	append();
}




