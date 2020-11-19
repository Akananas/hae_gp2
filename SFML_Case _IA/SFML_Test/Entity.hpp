#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
class Game;
enum State {
	Jumping,
	Running
};
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

	float gravity = 2;

	Game *game = nullptr;
	float jumpSpeed = -0.6;
	bool onGround = true;
	std::function<void(Entity&)> updateState;

	Entity(Game *g = nullptr) {
		sprite.setSize(sf::Vector2f(16, 64));
		sprite.setOrigin(sf::Vector2f(8, 64));
		radius = 16;
		game = g;
		onGround = true;
		updateState = std::mem_fn(&Entity::Move);
	}

	Entity(sf::RectangleShape _sprite) {
		sprite = _sprite;
		SetCoordinate(_sprite.getPosition());
		radius = 16;
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
	void SetCoordinate(sf::Vector2f pos) {
		xx = pos.x;
		yy = pos.y;
		cx = xx / GRID_SIZE;
		cy = yy / GRID_SIZE;
		rx = (xx - cx * GRID_SIZE) / GRID_SIZE;
		ry = (yy - cy * GRID_SIZE) / GRID_SIZE;
	}
	void MoveX();
	void MoveY();
	void SetSpriteCoor() {
		xx = (cx + rx) * GRID_SIZE;
		yy = (cy + ry) * GRID_SIZE;
		sprite.setPosition(sf::Vector2f(xx, yy));
	}
	bool hasCollision(int nextX, int nextY);
	void overlaps(Entity e);
	void jumpState();

	void Jump();
	void Move();

	void UpdateEntity(double dt) {
		if (updateState) {
			updateState(*this);
		}
		/*if (state == Jumping) {
			Jump(this);
		}
		if (state == Running) {
			Move(this);
		}*/
		dx *= 0.5;
		dy += dt * gravity;
		SetSpriteCoor();
	}
};
