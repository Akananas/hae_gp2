#pragma once
#include "Entity.hpp"

class Enemy : public Entity{
public:
	float hp = 5;
	float speed = 5.0;
	bool canMove = false;
	float spawnTime = 0;

	bool getDamage(float dmg);
	bool canHurtPlayer();
	void UpdateEntity(double dt, sf::Vector2i& playerPos);

};

