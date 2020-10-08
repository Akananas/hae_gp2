#pragma once
#include <stdlib.h>
class IntArray{
public:
	int* data = nullptr;
	int allocSize = 0;

	IntArray(int size) {
		data = (int*)malloc(size * sizeof(int));
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
		allocSize = size;
	}
	IntArray(const IntArray& arr) {
		int size = arr.allocSize;
		data = (int*)malloc(size * sizeof(int));
		this->allocSize = size;
		for (int i = 0; i < allocSize; i++) {
			data[i] = arr.data[i];
		}
	}
	~IntArray() {
		free(data);
	}
	
	void Resize(int newSize) {
		if (newSize > allocSize) {
			data = (int*)realloc(data,newSize * sizeof(int));
			for (int i = allocSize; i < newSize; i++) {
				data[i] = 0;
			}
			allocSize = newSize;
		}
	}
	
	int& Set(int index, int value) {
		if (index < 0) { throw "Index under min"; }
		if (index >= allocSize) { Resize(index + 1); }
		return data[index] = value;
	}

	int& Get(int index) {
		if (index < 0) { throw "Index under min"; }
		if (index >= allocSize) { throw "Index over max"; }
		return data[index];
	}

	int& operator[](int index) {
		return data[index];
	}

	int& operator()(int index) {
		return data[index];
	}

	static IntArray iota(int size) {
		IntArray arr(size);
		for (int i = 0; i < size; i++) {
			arr(i) = i;
		}
		return arr;
	}

	static IntArray random(int size) {
		IntArray arr(size);
		for (int i = 0; i < size; i++) {
			arr(i) = rand();
		}
		return arr;
	}

	int Search(int toFind) {
		for (int i = 0; i < allocSize; i++) {
			if (data[i] == toFind) {
				return i;
			}
		}
		return -1;
	}

	void push_front(int val) {
		insert(0, val);
	}	

	void push_back(int val) {
		Resize(allocSize + 1);
		data[allocSize-1] = val;
	}

	void insert(int pos, int val) {
		if (pos >= allocSize) { Resize(pos + 1); }
		else { Resize(allocSize + 1); }
		for (int i = allocSize-1; i > pos; i--) {
			data[i] = data[i - 1];
		}
		data[pos] = val;
	}
	int searchInsertionPos(int key) {
		for (int i = 1; i < allocSize; i++) {
			if (key > data[i-1] && key <= data[i]) {
				return i;
			}
		}
		return allocSize;
	}
 };

