#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include "Node.hpp"
#include "Node.cpp"
#include "DynArr.hpp"
#include "IntArray.hpp"
#include <functional>
#include "Lib.hpp"
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
void MemCpy(char* dst, char* src, int size){
	for (int i = 0; i < size; i++) {
		*dst = *src;
		dst++;
		src++;
	}
}

char* StrChr(char* grange, char chat) {
	if (*grange == chat) {
		return grange;
	}
	if (!*grange) {
		return nullptr;
	}
	return StrChr(++grange, chat);
}
int StrLen(char* meule) {
	int len = 0;
	while (*meule) {
		meule++;
		len++;
	}
	return len;
}
bool startsWith(char* meule, char* aiguille) {
	int lMeule = StrLen(meule);
	int lAiguille = StrLen(aiguille);

	if (lAiguille > lMeule)
		return false;

	for (int i = 0; i < lAiguille; i++) {
		if (aiguille[i] != meule[i]) {
			return false;
		}
	}
	return true;
}
char* StrStr(char* meuleDeFoin, char* aiguille) {
	if (aiguille == nullptr && meuleDeFoin == nullptr) {
		return nullptr;
	}
	if (meuleDeFoin == nullptr) {
		return nullptr;
	}
	if (*meuleDeFoin == 0) {
		return nullptr;
	}
	if (startsWith(meuleDeFoin, aiguille)) {
		return meuleDeFoin;
	}
	else {
		return StrStr(++meuleDeFoin, aiguille);
	}
}

void subFunction4() {
	char data[] = { 1,2,3,4,5,6 };
	char* dest = (char*)malloc(16);
	for (int i = 0; i < 16; ++i){
		dest[i] = 0;
	}
	MemCpy(dest, data, sizeof(data) * sizeof(char));
	free(dest);
	char* res;
	char find[] = "meule";
	char data2[] = "zmeuleaze";
	res = StrChr(data, 1);
	res = StrStr(data2,find);
	std::cout << std::endl;
}
int add(int a, int b) {
	if (b == 0) { return a; }
	if (b < 0) {
		return add(a - 1, b + 1);
	}else {
		return add(a + 1, b - 1);
	}
}
int sub(int a, int b) {
	if (b == 0) { return a; }
	if (b < 0) { 
		return sub(a + 1, b + 1);
	}else {
		return sub(a - 1, b - 1);
	}
}
int mul(int a, int b) {
	if (b == 0) { return 0; }
	if (b < 0) {
		return -a + mul(a, b + 1);
	}
	else if(b > 0){
		return a + mul(a, b - 1);
	}
}

int divide(int a, int b) {
	if (b == 0) { throw "Error: Trying to divide by 0"; }
	if (b == 1) { return a; }
	if (b < 0) { return -divide(a, -b); }
	if (a < 0) { return -divide(-a, b); }
	if (a < b) { return 0; }
	return 1 + divide(a - b, b);
}

int modulo(int a, int b) {
	if (b == 0) { throw "Error: Trying to divide by 0"; }
	if (b == 1) { return 0; }
	if (b < 0) { return -modulo(a, -b); }
	if (a < 0) { return -modulo(-a, b); }
	if (a < b) { return a; }
	return modulo(a - b, b);
}


void subFunction5() {
	std::cout << add(5, -6) << std::endl;
	std::cout << sub(5, -6) << std::endl;
	std::cout << mul(5, 6) << std::endl;
	std::cout << divide(-20, 5) << std::endl;
	std::cout << modulo(-10,-3) << std::endl;
}
int StrCmp(const char* a, const char* b) {
	if (!*a && !*b) {
		return 0;
	}
	if (!*b) {
		return 1;
	}
	else if (!*a) {
		return -1;
	}
	if (*a == *b) {
		return StrCmp(a+1, b+1);
	}
	if (*a > * b) {
		return 1;
	}
	return -1;
}
void subFunction6() {
	char mot1[] = "chat";
	char mot2[] = "chien";
	int res = StrCmp(mot1, mot2);
	std::cout << std::endl;
}
void subFunction7() {
	IntArray a = IntArray::iota(5);
	a.push_front(10);
	a.push_back(10);
	a.insert(3, 10);
	int find = a.Search(3);
	int find2 = a.Search(20);
	int insertAt2 = a.searchInsertionPos(1);
	int insertAt3 = a.searchInsertionPosRec(1);
	a.insert(a.searchInsertionPos(20), 20);
	a.insert(a.searchInsertionPos(1), 1);
	a = *IntArray::sort(&a,a.allocSize);
	int insertAt6 = a.searchInsertionPos(4);
	int insertAt4 = a.binarySearch(4,0,a.allocSize-1);
	int insertAt5 = a.binarySearch(250,0,a.allocSize-1);
	a.insert(a.binaryInsertSearch(15,0,a.allocSize - 1), 15);
	a.insert(a.binaryInsertSearch(25,0,a.allocSize - 1), 25);
	a.insert(a.binaryInsertSearch(-1,0,a.allocSize - 1), -1);
	a.insert(a.binaryInsertSearch(250,0,a.allocSize - 1), 250);
	std::cout << std::endl;
}
int main() {
	//subFunction();
	//heapSort();
	//append();
	//subFunction4();
	//subFunction5();
	//subFunction6();
	subFunction7();
}




