#include "Bullet.hpp"

Bullet::Bullet(Game* g, sf::Vector2f spawnPos, sf::Vector2f dir) {
	dx = dir.x;
	dy = dir.y;
	sprite.setSize(sf::Vector2f(16, 16));
	sprite.setOrigin(sf::Vector2f(8, 8));
	sprite.setFillColor(sf::Color(247, 249, 118));
	SetPosition(spawnPos);
	radius = 16;
	game = g;
	explosionColor = sf::Color(247, 249, 118);
}

void Bullet::UpdateEntity(double dt) {
	MoveX();
	MoveY();
	SetSpriteCoor();
}

void Bullet::MoveY() {
	ry += dy;
	if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
		destroyed = true;
		ry = 0;
	}
	if (hasCollision(cx, cy - radius / GRID_SIZE) && ry <= 0.3) {
		destroyed = true;
		ry = 0;
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
		rx = 0;
	}
	if (hasCollision(cx - radius / GRID_SIZE, cy) && rx <= 0.3) {
		destroyed = true;
		rx = 0;
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
