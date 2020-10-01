#pragma once
#include <functional>
template<typename T>
class DynArr {
public:
	T* data = nullptr;
	size_t allocSize = 0;
	DynArr(int size) {
		this->allocSize = size;
		data = (T*)malloc(size * sizeof(T));
		for (int i = 0; i < size; i++) {
			data[i] = {};
		}
	};

	virtual ~DynArr() {
		free(data);
	};

	T& Get(int index) {
		if (index > allocSize || index < 0) { throw "assert:out of bound"; }
		return data[index];
	};
	void Set(int index, const T & value) {
		if (index < 0) { throw "assert:out of bound"; }
		if (index >= allocSize) { Resize(index + 1); }
		data[index] = value;
	};
	void Resize(int newAllocSize) {
		if (newAllocSize < allocSize)
			return;
		int allocSizeByte = newAllocSize * sizeof(T);
		data = (T*)realloc(data, allocSizeByte);
		for (int i = allocSize; i < newAllocSize; ++i) {
			data[i] = {};
		}
		allocSize = newAllocSize;
	};
	void Reverse() {
		int lastIndex = allocSize - 1;
		for (int i = 0; i < ceil(allocSize / 2.0); i++) {
			T a = data[i];
			data[i] = data[lastIndex - i];
			data[lastIndex - i] = a;
		}
	}

	int length() const {
		return allocSize;
	}
	void push_back(const T & elem) {
		Set(allocSize, elem);
	}

	void append(const DynArr<T> & arr) {
		for (int i = 0; i < arr.allocSize; i++) {
			this->push_back(arr.data[i]);
		}
	}

	void iter( std::function< void(T) > _iter ) {
		for (int i = 0; i < length(); i++) {
			_iter(data[i]);
		}
	}
};