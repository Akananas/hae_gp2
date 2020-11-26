#include "Entity.hpp"
#include "Game.hpp"

void Entity::MoveX() {
	rx += dx * speedMul;
	if (hasCollision(cx + radius / GRID_SIZE, cy) && rx >= 0.7) {
		rx = 0.7;
		dx = 0; // stop movement
		IdleState();
	}
	if (hasCollision(cx - radius / GRID_SIZE, cy) && rx <= 0.3) {
		rx = 0.3;
		dx = 0;
		IdleState();
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
	ry += dy * speedMul;
	if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
		ry = 0.7;
		dy = 0;
		IdleState();
	}

	if (hasCollision(cx, cy - radius / GRID_SIZE) && ry <= 0.3) {
		ry = 0.3;
		dy = 0;
		IdleState();
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
	if (path[0] == sf::Vector2i(cx, cy)) {
		path.erase(path.begin());
		if (path.size() <= 0) {
			dy = 0;
			dx = 0;
			IdleState();
		}
		else {
			RecalculateDir();
		}
	}
}

void Entity::MoveTo(std::vector<sf::Vector2i>& pos) {
	path.clear();
	path = pos;
	if (path[0] == sf::Vector2i(cx, cy)) {
		IdleState();
		return;
	}
	RecalculateDir();
	if (!moving) {
		if (speedMul == 0.5f) {
			Walk();
		}
		else {
			Run();
		}
		updateState = std::mem_fn(&Entity::Move);
		moving = true;
	}
}

void Entity::UpdateEntity(double dt) {
	if (updateState) {
		updateState(*this);
	}
	SetSpriteCoor();
}
