
#include "pch.h"
#include <iostream>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vec2T.hpp"
#include "Vec3T.hpp"
#include "Arr.hpp"
#include <string>
using namespace std;
void SubFunction() {
	Arr<int> arr(4);
	cout << arr.Get(0) << endl;
	arr.Set(2, 120);
	cout << arr.Get(2) << endl;
}
int main() {
	/*Vector3 v1(3, 2, 5);
	Vector3 v2(4, 6, 1);
	Vector3 cross = v1.Cross(v2);
	cout << to_string(cross.x) << " " << to_string(cross.y) << " " << to_string(cross.z) << " " << to_string(cross.Mag());
	Vec3T<int> t0(3,5,2);
	Vec3T<float> t1(4.5, 2, 3.25);
	auto tres = t1.Mul(2);
	cout << to_string(tres.x) << " " << to_string(tres.y) << " " << to_string(tres.z);*/
	/*int tab[] = { 0,1,2,3,4 };
	for (int i = 0; i < sizeof(tab)/sizeof(tab[0]); i++) {
		cout << to_string(tab[i]) << " ";
	}

	int* c0 = tab;
	int* c1 = &(tab[0]);

	int valC = *c0++;*/
	/*Vector2 sapin(33, 44);
	Vector2 sapin2(55, 55);
	sapin.incr(&sapin2);
	cout << to_string(sapin2.x) << endl;*/
	SubFunction();
	cout << endl;
 }


