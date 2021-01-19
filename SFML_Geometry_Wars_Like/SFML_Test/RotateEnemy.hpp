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
		speed = 80;
	}

	void UpdateEntity(double dt, sf::Vector2i& playerPos) override;

	void MoveX(double dt);

	void MoveY(double dt);
};

