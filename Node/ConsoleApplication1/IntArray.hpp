#pragma once
class IntArray{
public:
	int* data;
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
			realloc(data,newSize * sizeof(int));
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
		Resize(allocSize + 1);

	}
 };

