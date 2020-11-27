#pragma once
#include "Entity.hpp"

class Player :public Entity {
public:
	float damage;
	int bomb;
	float attackSpeed;
	int life;
	bool isAlive = false;
	double spawnTimer;
	sf::Vector2f baseSize = sf::Vector2f(32, 32);
	Player() {}
	Player(Game* g) {
		sprite.setSize(baseSize);
		sprite.setOrigin(sf::Vector2f(16, 16));
		radius = 16;
		game = g;
		damage = 1;
		life = 3;
		attackSpeed = 0.2f;
		spawnTimer = 0;
	}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Player*>(type)) {
			return true;
		}
		return false;
	}
	void UpdateEntity(double dt) {
		if (isAlive) {
			Entity::UpdateEntity(dt);
			dx *= 0.5;
			dy *= 0.5;
		}
		else {
			SpawnPlayer(dt);
		}
	}
	void SpawnPlayer(double dt) {
		if (spawnTimer >= 0.75) {
			isAlive = true;

		}
		else {
			spawnTimer += dt;
			sprite.setScale(sf::Vector2f(spawnTimer / 0.75, spawnTimer / 0.75));
		}
	}

	void KillPlayer() {
		spawnTimer = 0;
		isAlive = false;
	}
};

