#pragma once
#include "SFML/Graphics.hpp"

class Entity {
public:
	static const int GRID_SIZE = 16;
	sf::RectangleShape sprite;
	float radius = 0;
	// Base coordinates
	int cx = 0;
	int cy = 0;
	float rx = 0;
	float ry = 0;

	// Resulting coordinates
	float xx = 0;
	float yy = 0;

	// Movements
	float dx = 0;
	float dy = 0;

	Entity() {
		sprite.setSize(sf::Vector2f(16, 64));
		sprite.setOrigin(sf::Vector2f(8, 64));
		radius = 32;
	}
	void SetPosition(sf::Vector2u pos) {
		sprite.setPosition(sf::Vector2f(pos.x / 2, pos.y / 2));
		SetCoordinate(pos.x / 2, pos.y / 2);
	}
	void SetPosition(int x, int y) {
		sprite.setPosition(sf::Vector2f(x, y));
		SetCoordinate(x, y);
	}
	void SetCoordinate(float x, float y) {
		xx = x;
		yy = y;
		cx = xx / GRID_SIZE;
		cy = yy / GRID_SIZE;
		rx = (xx - cx * GRID_SIZE) / GRID_SIZE;
		ry = (yy - cy * GRID_SIZE) / GRID_SIZE;
	}

	void MoveX() {
		rx += dx;
		ry += dy;
		if (hasCollision(cx + radius /GRID_SIZE, cy) && rx >= 0.7) {
			rx = 0.7;
			dx = 0; // stop movement
		}
		if (hasCollision(cx - radius/2 / GRID_SIZE, cy) && rx <= 0.3) {
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
	void MoveY() {
		if (hasCollision(cx, cy + radius / GRID_SIZE) && ry >= 0.7) {
			ry = 0.7;
			dy = 0; // stop movement
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
	void SetSpriteCoor() {
		xx = (cx + rx) * GRID_SIZE;
		yy = (cy + ry) * GRID_SIZE;
		sprite.setPosition(sf::Vector2f(xx, yy));
	}
	bool hasCollision(int nextX, int nextY);
	bool overlaps(Entity e) {
		float maxDist = radius + e.radius;
		float distSqr = (e.xx - xx) * (e.xx - xx) + (e.yy - yy) * (e.yy - yy);
		return distSqr <= maxDist * maxDist;
	}
	void UpdateEntity() {
		MoveX();
		MoveY();
		dx *= 0.5;
		dy *= 0.5;
		SetSpriteCoor();
	}
};
