#include "RotateEnemy.hpp"

void RotateEnemy::UpdateEntity(double dt, sf::Vector2i& playerPos) {
	if (canMove) {
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
		else if (rotating == true && rotatingTimer <= 2.5) {
			rotatingTimer += dt;
			sprite.rotate(1080 * dt * rotatingTimer / 2.6);
			if (!changeColor && rotatingTimer  >= 2) {
				changeColor = true;
				colorTimer = 0;
			}
		}
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
