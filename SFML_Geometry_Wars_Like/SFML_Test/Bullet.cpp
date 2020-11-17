#include "Bullet.hpp"

void Bullet::MoveY() {
	ry += dy;
	if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
		destroyed = true;
	}
	if (hasCollision(cx, cy - radius / GRID_SIZE) && ry <= 0.3) {
		destroyed = true;
	}
	while (ry > 1) {
		ry--;
		cy++;
	}
	while (ry < 0) {
		ry++;
		cy--;
	}
}

void Bullet::MoveX() {
	rx += dx;
	if (hasCollision(cx + radius / GRID_SIZE, cy) && rx >= 0.7) {
		destroyed = true;
	}
	if (hasCollision(cx - radius / GRID_SIZE, cy) && rx <= 0.3) {
		destroyed = true;
	}
	while (rx > 1) {
		rx--;
		cx++;
	}
	while (rx < 0) {
		rx++;
		cx--;
	}
}
