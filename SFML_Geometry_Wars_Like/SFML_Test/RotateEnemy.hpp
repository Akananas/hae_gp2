#pragma once
#include "Enemy.hpp"
class RotateEnemy : public Enemy {
public:
	bool rotating = false;
	bool changeColor = false;
	sf::Color readyColor = sf::Color(217, 53, 39);
	sf::Color normalColor;
	float rotatingTimer = 0;
	float colorTimer = 0;
	RotateEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col) {
		this->game = g;
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(_col);
		normalColor = _col;
		radius = 16;
		hp = 1 * level;
		SetPosition(spawn);
		canMove = false;
		spawnTime = 0;
		speed = 1;
	}

	void UpdateEntity(double dt, sf::Vector2i& playerPos) override;

	void MoveX() {
		rx += dx;
		if (hasCollision(cx + radius / GRID_SIZE, cy) && rx >= 0.7) {
			rx = 0.7;
			dx = -dx; // stop movement
		}
		if (hasCollision(cx - radius / GRID_SIZE, cy) && rx <= 0.3) {
			rx = 0.3;
			dx = -dx;
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

	void MoveY() {
		ry += dy;
		if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
			ry = 0.7;
			dy = -dy;
		}
		if (hasCollision(cx, cy - radius / GRID_SIZE) && ry <= 0.3) {
			ry = 0.3;
			dy = -dy;
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
};

