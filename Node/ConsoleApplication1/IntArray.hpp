#pragma once
#include <stdlib.h>
#include <cmath>

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
	bool isSorted(int pos = 0) {
		if (pos+1 >= allocSize) {
			return true;
		}
		if (data[pos] <= data[pos + 1]) {
			return isSorted(pos + 1);
		}
		return false;
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
	int searchInsertionPosRec(int key, int pos = 0) {
		if (pos >= allocSize) return allocSize;
		if (data[pos] >= key) {
			return pos;
		}
		return searchInsertionPosRec(key, pos + 1);
	}
	int searchPosRec(int key, int pos = 0) {
		if (pos >= allocSize) {
			return -1;
		}
		if (data[pos] == key) {
			return pos;
		}
		return searchPosRec(key, pos+1);
	}

	int binarySearch(int key, int start, int end) {
		if (start > end) {
			return -1;
		}
		int middle = (end + start + 1) / 2;
		if (data[start] == key) { return start; }
		if (data[middle] == key) { return middle; }
		if (data[end] == key) { return end; }

		if (data[middle] > key) {
			return binarySearch(key, start, middle - 1);
		}else {
			return binarySearch(key, middle + 1, end);
		}
	}

	int binaryInsertSearch(int key, int start, int end) {
		if (start > end || start >= allocSize) {
			return allocSize;
		}
		if (0 == start && 0 == end) {
			return 0;
		}
		int middle = (end + start + 1) / 2;
		if (data[middle] > key && data[middle-1] > key) {
			return binaryInsertSearch(key, start , middle - 1);
		}else if(data[middle] < key && data[middle+1] < key){
			return binaryInsertSearch(key, middle +1, end);
		}else if (data[middle] > key) {
			return (middle - 1);
		}else {
			return (middle + 1);
		}
	}
	void permuter(int oldVal, int newVal) {
		int tmpVal = data[oldVal];
		data[oldVal] = data[newVal];
		data[newVal] = tmpVal;
	}
	static IntArray* sort(IntArray* tab, int tabSize) {
		for (int i = 1; i < tabSize; i++) {
			int j = i;
			while (j > 0 && tab->data[j] < tab->data[j - 1]) {
				tab->permuter(j, j - 1);
				j--;
			}
		}
		return tab;
	}
 };

