#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;
class interp {
public:
	static Vector2f lerp(Vector2f v0, Vector2f v1, float t) {
		float tx = (v1.x - v0.x) * t + v0.x;
		float ty = (v1.y - v0.y) * t + v0.y;
		return Vector2f(tx, ty);
	}
};