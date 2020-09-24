#pragma once
#include <math.h>  
class Vector3 {
public:
	float x, y, z;
	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float Mag() {
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	Vector3 Add(Vector3 otherVec) {
		return Vector3(
			this->x + otherVec.x,
			this->y + otherVec.y,
			this->z + otherVec.z
		);
	}
	Vector3 Sub(Vector3 otherVec) {
		return Vector3(
			this->x - otherVec.x,
			this->y - otherVec.y,
			this->z - otherVec.z
		);
	}
	Vector3 Mul(Vector3 otherVec) {
		return Vector3(
			this->x * otherVec.x,
			this->y * otherVec.y,
			this->z * otherVec.z
		);
	}
	Vector3 Mul(float scalar) {
		return Vector3(
			this->x * scalar,
			this->y * scalar,
			this->z * scalar
		);
	}
	Vector3 Div(Vector3 otherVec) {
		return Vector3(
			this->x / otherVec.x,
			this->y / otherVec.y,
			this->z / otherVec.z
		);
	}
	float Dot(Vector3 otherVec) {
		return this->x * otherVec.x + this->y * otherVec.y + this->z * otherVec.z;
	}
	Vector3 Cross(Vector3 otherVec) {
		return Vector3(
			this->y * otherVec.z - this->z * otherVec.y,
			this->z * otherVec.x - this->x * otherVec.z,
			this->x * otherVec.y - this->y * otherVec.x
		);
	}
};