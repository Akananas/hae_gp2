#pragma once
#include "Entity.hpp"

class Ennemy : public Entity{
public:
	float hp;
	float speed = 5.0;
	bool canMove = false;
	float spawnTime = 0;
	Ennemy() {
		hp = 5;
	}
	Ennemy(Game* g, int level, float x, float y, sf::Color _col) {
		this->game = g;
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(_col);
		radius = 16;
		hp = 2 * level;
		SetPosition(x, y);
		canMove = false;
		spawnTime = 0;
	}
	Ennemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col) {
		this->game = g;
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(_col);
		radius = 16;
		hp = 2 * level;
		SetPosition(spawn);
		canMove = false;
		spawnTime = 0;
	}
	bool getDamage(float dmg) {
		hp -= dmg;
		if (hp <= 0) {
			destroyed = true;
		}
		return destroyed;
	}
	bool canHurtPlayer() {
		return canMove;
	}
	void UpdateEntity(double dt, sf::Vector2i& playerPos);

};

