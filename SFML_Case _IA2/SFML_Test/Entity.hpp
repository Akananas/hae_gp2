#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
class Game;

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

	float speedMul = 0;
	Game* game = nullptr;
	std::function<void(Entity&)> updateState;
	bool moving = false;
	sf::Vector2i targetPos;
	std::vector<sf::Vector2i> path;
	Entity(Game* g = nullptr) {
		sprite.setSize(sf::Vector2f(16, 64));
		sprite.setOrigin(sf::Vector2f(8, 64));
		radius = 16;
		game = g;
		moving = false;
		updateState = std::mem_fn(&Entity::Idle);
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
	void ChangeSpeed(float x, float y) {
		dx = x;
		dy = y;
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
	void Move();
	void Walk() {
		speedMul = 0.5f;
		sprite.setFillColor(sf::Color::Green);
	}
	void Run() {
		speedMul = 1.f;
		sprite.setFillColor(sf::Color::Blue);
	}
	void IdleState() {
		moving = false;
		sprite.setFillColor(sf::Color::Yellow);
		updateState = std::mem_fn(&Entity::Idle);
	}
	void Idle() {
		if (hasCollision(cx, cy + radius / GRID_SIZE) || hasCollision(cx, cy - radius / GRID_SIZE)
			|| hasCollision(cx + radius /GRID_SIZE, cy) || hasCollision(cx - radius / GRID_SIZE, cy) ) {
			CoverState();
		}	
	}
	void Cover() {
		if (!hasCollision(cx, cy + radius / GRID_SIZE) && !hasCollision(cx, cy - radius / GRID_SIZE)
			&& !hasCollision(cx + radius / GRID_SIZE, cy) && !hasCollision(cx - radius / GRID_SIZE, cy)) {
			IdleState();
		}
	}
	void CoverState() {
		sprite.setFillColor(sf::Color::Red);
		updateState = std::mem_fn(&Entity::Cover);
	}
	void RecalculateDir() {
		sf::Vector2i dir = (path[0] - sf::Vector2i(cx, cy));
		dx = dir.x / 4.0;
		dy = dir.y / 4.0;
	}

	void MoveTo(std::vector<sf::Vector2i>& pos);
	void UpdateEntity(double dt);
};