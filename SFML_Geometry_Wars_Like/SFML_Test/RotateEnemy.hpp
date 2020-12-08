#pragma once
#include "Enemy.hpp"
class RotateEnemy : public Enemy {
public:
	bool rotating = false;
	float rotatingTimer = 0;
	RotateEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col) {
		this->game = g;
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(_col);
		radius = 16;
		hp = 1 * level;
		SetPosition(spawn);
		canMove = false;
		spawnTime = 0;
		speed = 1.5;
	}

	void UpdateEntity(double dt, sf::Vector2i& playerPos) override {
		if (canMove) {
			if (rotating == false && rotatingTimer > 2.5) {
				MoveX();
				MoveY();
				SetSpriteCoor();
				float friction = 1.0f / (1 + 1.f * float(dt));
				dx *= friction;
				dy *= friction;
				if (abs(dx) < 0.1 && abs(dy) < 0.1) {
					rotatingTimer = 0;
					rotating = true;
					dx = 0;
					dy = 0;
				}
			}
			else if (rotating == true && rotatingTimer > 2.5) {
				rotating = false;
				sf::Vector2i curPos(cx, cy);
				sf::Vector2f dir(playerPos - curPos);
				dir = normalized(dir);
				dx = dir.x * speed;
				dy = dir.y * speed;
			}
			else if (rotating == true && rotatingTimer <= 2.5) {
				rotatingTimer += dt;
				sprite.rotate(10 * rotatingTimer / dt);
			}
		}
		else {
			if (spawnTime > 0.35) {
				canMove = true;
				rotating = true;
				rotatingTimer = 0;
			}
			else {
				spawnTime += dt;
				sprite.setScale(sf::Vector2f(spawnTime / 0.35, spawnTime / 0.35));
			}
		}
	}

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

