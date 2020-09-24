#pragma once
template<typename T>
class Vec2T {
public:
	T x;
	T y;
	Vec2T<T>() {
		x = {};
		y = {};
	}
	Vec2T<T>(T x, T y) {
		this->x = x;
		this->y = y;
	}
	Vec2T<T> Add(Vec2T otherVec) {
		Vec2T<T> res;
		res.x = this->x + otherVec.x;
		res.y = this->y + otherVec.y;
		return res;
	}
	Vec2T<T> Add(T x, T y) {
		Vec2T<T> res;
		res.x = this->x + x;
		res.y = this->y + y;
		return res;
	}
	Vec2T<T> Sub(Vec2T otherVec) {
		Vec2T<T> res;
		res.x = this->x - otherVec.x;
		res.y = this->y - otherVec.y;
		return res;
	}
	Vec2T<T> Sub(T x, T y) {
		Vec2T<T> res;
		res.x = this->x - x;
		res.y = this->y - y;
		return res;
	}
	Vec2T<T> Mul(Vec2T otherVec) {
		Vec2T<T> res;
		res.x = this->x * otherVec.x;
		res.y = this->y * otherVec.y;
		return res;
	}
	Vec2T<T> Mul(int scalar) {
		Vec2T<T> res;
		res.x = this->x * scalar;
		res.y = this->y * scalar;
		return res;
	}
	Vec2T<T> Div(Vec2T otherVec) {
		Vec2T<T> res;
		res.x = this->x / otherVec.x;
		res.y = this->y / otherVec.y;
		return res;
	}
	Vec2T<T> Div(int scalar) {
		Vec2T<T> res;
		res.x = this->x / scalar;
		res.y = this->y / scalar;
		return res;
	}
};