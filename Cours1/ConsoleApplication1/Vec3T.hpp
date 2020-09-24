#pragma once
template<typename T> 

class Vec3T {
public:
	T x;
	T y;
	T z;

	Vec3T() {
		x = {};
		y = {};
		z = {};
	}
	Vec3T(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3T Add(Vec3T otherVec) {
		Vec3T<T> res;
		res.x = this->x + otherVec.x;
		res.y = this->y + otherVec.y;
		res.z = this->z + otherVec.z;
		return res;
	}
	Vec3T Sub(Vec3T otherVec) {
		Vec3T<T> res;
		res.x = this->x - otherVec.x;
		res.y = this->y - otherVec.y;
		res.z = this->z - otherVec.z;
		return res;
	}
	Vec3T Mul(Vec3T otherVec) {
		Vec3T<T> res;
		res.x = this->x * otherVec.x;
		res.y = this->y * otherVec.y;
		res.z = this->z * otherVec.z;
		return res;
	}
	Vec3T Mul(float scalar) {
		Vec3T<T> res;
		res.x = this->x * scalar;
		res.y = this->y * scalar;
		res.z = this->z * scalar;
		return res;
	}
	Vec3T Div(Vec3T otherVec) {
		Vec3T<T> res;
		res.x = this->x / otherVec.x;
		res.y = this->y / otherVec.y;
		res.z = this->z / otherVec.z;
		return res;
	}
	Vec3T Div(float scalar) {
		Vec3T<T> res;
		res.x = this->x / scalar;
		res.y = this->y / scalar;
		res.z = this->z / scalar;
		return res;
	}
};