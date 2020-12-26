#include "RotateEnemy.hpp"

void RotateEnemy::UpdateEntity(double dt, sf::Vector2i& playerPos) {
	if (canMove) {
		// Moving
		if (rotating == false && rotatingTimer > 2.5) {
			MoveX();
			MoveY();
			SetSpriteCoor();
			float friction = 1.0f / (1 + 0.5f * float(dt));
			dx *= friction;
			dy *= friction;
			if (abs(dx) < 0.1 && abs(dy) < 0.1) {
				rotatingTimer = 0;
				rotating = true;
				dx = 0;
				dy = 0;
				sprite.setFillColor(normalColor);
			}
		}
		//Stop rotation
		else if (rotating == true && rotatingTimer > 2.5) {
			rotating = false;
			sf::Vector2i curPos(cx, cy);
			sf::Vector2f dir(playerPos - curPos);
			dir = normalized(dir);
			dx = dir.x * speed;
			dy = dir.y * speed;
			sprite.setFillColor(readyColor);
			changeColor = false;
		}
		//Rotate
		else if (rotating == true && rotatingTimer <= 2.5) {
			rotatingTimer += dt;
			sprite.rotate(1080 * dt * rotatingTimer / 2.6);
			//Start changing color
			if (!changeColor && rotatingTimer  >= 2) {
				changeColor = true;
				colorTimer = 0;
			}
		}
		//Change color
		if (colorTimer >= 0.1 && changeColor) {
			if (sprite.getFillColor() != readyColor) {
				sprite.setFillColor(readyColor);
			}
			else {
				sprite.setFillColor(normalColor);
			}
			colorTimer = 0;
		}
		if (changeColor) {
			colorTimer += dt;
		}
	}
	//Spawning
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

inline void RotateEnemy::MoveX() {
	rx += dx;
	if (hasCollision(cx + radius / GRID_SIZE, cy) && rx >= 0.7) {
		rx = 0.7;
		dx = -dx; 
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

inline void RotateEnemy::MoveY() {
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
