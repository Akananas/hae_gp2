#include "Entity.hpp"
#include "Game.hpp"

void Entity::SetCoordinate(float x, float y) {
	xx = x;
	yy = y;
	cx = xx / GRID_SIZE;
	cy = yy / GRID_SIZE;
	rx = (xx - cx * GRID_SIZE) / GRID_SIZE;
	ry = (yy - cy * GRID_SIZE) / GRID_SIZE;
}

void Entity::SetCoordinate(sf::Vector2f pos) {
	SetCoordinate(pos.x, pos.y);
}

void Entity::MoveX(double dt) {
	rx += dx * dt;
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

void Entity::MoveY(double dt) {
	ry += dy * dt;
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

void Entity::SetSpriteCoor() {
	xx = (cx + rx) * GRID_SIZE;
	yy = (cy + ry) * GRID_SIZE;
	sprite.setPosition(sf::Vector2f(xx, yy));
}

bool Entity::hasCollision(int nextX, int nextY) {
	return game->isWall(nextX,nextY);
}
void Entity::Pushback(Entity e) {
	float dist = sqrt((e.xx - xx) * (e.xx - xx) + (e.yy - yy) * (e.yy - yy));
	float ang = atan2(e.yy - yy, e.xx - xx);
	float force = 1;
	float repelPower = (radius + e.radius - dist) / (radius + e.radius);
	dx -= cos(ang) * repelPower * force;
	dy -= sin(ang) * repelPower * force;
}
void Entity::UpdateEntity(double dt) {
	MoveX(dt);
	MoveY(dt);
	SetSpriteCoor();
}
bool Entity::overlaps(Entity e) {
	float dist = sqrt((e.xx - xx) * (e.xx - xx) + (e.yy - yy) * (e.yy - yy));
	if (dist <= radius + e.radius) {
		return true;
	}
	return false;
}

