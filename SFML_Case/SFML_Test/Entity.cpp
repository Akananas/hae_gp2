#include "Entity.hpp"
bool Entity::hasCollision(int nextX, int nextY) {
	if (nextX >= 1280/GRID_SIZE || nextY >= 720/GRID_SIZE) {
		return true;
	}
	if (nextX <= 0 || nextY <= 0) {
		return true;
	}
	return false;
}
