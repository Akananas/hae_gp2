#pragma once
#include "Enemy.hpp"
class Boss : public Enemy{
public:
	Boss(Game* g, int level, sf::Vector2f spawn) {
			this->game = g;
			sprite.setSize(sf::Vector2f(64, 64));
			sprite.setOrigin(sf::Vector2f(32, 32));
			sprite.setFillColor(sf::Color(105, 18, 92));
			radius = 32;
			hp = 50 * level;
			SetPosition(spawn);
			canMove = false;
			spawnTime = 0;
			speed = 10;
	}
};

