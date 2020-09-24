#pragma once
template<typename T>
class Arr {
public:
	T* data = nullptr;
	int size = 0;
	Arr<T>(int _size) {
		data = new T[_size];
		for (int i = 0; i < _size; i++) {
			data[i] = {};
		}
		this->size = _size;
	}
	virtual ~Arr() {
		delete[] data;
		cout << "deleted" << endl;
	}

	T & Get(int index) {
		if (index >= size) { throw "out of bound max"; }
		if (index < 0) { throw "out of bound min"; }
		return data[index];
	}
	void Set(int index, T val) {
		if (index >= size) { throw "out of bound max"; } 
		if (index < 0) { throw "out of bound min"; }
		data[index] = val;
	}
};