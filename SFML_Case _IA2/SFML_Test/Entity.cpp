#include "Entity.hpp"
#include "Game.hpp"

void Entity::MoveX() {
	rx += dx;
	if (hasCollision(cx + radius / GRID_SIZE, cy) && rx >= 0.7) {
		rx = 0.7;
		dx = 0; // stop movement
	}
	if (hasCollision(cx - radius / GRID_SIZE, cy) && rx <= 0.3) {
		rx = 0.3;
		dx = 0;
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

void Entity::MoveY() {
	ry += dy;
	if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
		ry = 0.7;
		dy = 0;
	}

	if (hasCollision(cx, cy - radius / GRID_SIZE) && ry <= 0.3) {
		ry = 0.3;
		dy = 0;
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

bool Entity::hasCollision(int nextX, int nextY) {
	return game->isWall(nextX, nextY);
}

void Entity::overlaps(Entity e) {
	float dist = sqrt((e.xx - xx) * (e.xx - xx) + (e.yy - yy) * (e.yy - yy));
	if (dist <= radius + e.radius) {
		float ang = atan2(e.yy - yy, e.xx - xx);
		float force = 1.5;
		float repelPower = (radius + e.radius - dist) / (radius + e.radius);
		dx -= cos(ang) * repelPower * force;
		dy -= sin(ang) * repelPower * force;
	}
}


void Entity::Move() {
	MoveX();
	MoveY();
}