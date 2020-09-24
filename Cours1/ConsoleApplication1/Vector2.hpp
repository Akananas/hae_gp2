#pragma once
#include <math.h>  
class Vector2 {
public:
	float x, y;
	Vector2() {
		this->x = 0;
		this->y = 0;
	}
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	float Mag() {
		return sqrt(this->x * this->x + this->y * this->y);
	}
	Vector2 Add(Vector2 otherVec) {
		return Vector2(
			this->x + otherVec.x,
			this->y + otherVec.y
		);
	}
	Vector2 Sub(Vector2 otherVec) {
		return Vector2(
			this->x - otherVec.x,
			this->y - otherVec.y
		);
	}
	Vector2 Mul(Vector2 otherVec) {
		return Vector2(
			this->x * otherVec.x,
			this->y * otherVec.y
		);
	}
	Vector2 Mul(float scalar) {
		return Vector2(
			this->x * scalar,
			this->y * scalar
		);
	}
	Vector2 Div(Vector2 otherVec) {
		return Vector2(
			this->x / otherVec.x,
			this->y / otherVec.y
		);
	}
	float Dot(Vector2 otherVec) {
		return this->x * otherVec.x + this->y * otherVec.y;
	}
};