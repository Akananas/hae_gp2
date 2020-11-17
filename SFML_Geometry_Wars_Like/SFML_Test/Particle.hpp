#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class Particle : public Entity{
public:
	bool destroyed = false;
	float life = 1.0;
	Particle(Game* g, sf::Vector2f spawnPos, sf::Vector2f speed, sf::Color color) {
		dx = speed.x;
		dy = speed.y;
		sprite.setSize(sf::Vector2f(8, 8));
		sprite.setOrigin(sf::Vector2f(4, 4));
		sprite.setFillColor(color);
		SetPosition(spawnPos);
		radius = 4;
		game = g;
	}
	~Particle() {}

	void UpdateEntity(double dt) {
		MoveX();
		MoveY();
		SetSpriteCoor();
		life -= dt;
		if (life < 0) {
			destroyed = true;
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
};