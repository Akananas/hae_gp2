#pragma once
#include "Entity.hpp"
struct SaveFile;
class Player :public Entity {
public:
	float damage =  1;
	int damageLevel =  1;
	int bomb = 3;
	float bombRadius = 250;
	float attackSpeed = 0.2;
	int attackSpeedLevel = 1;
	bool isAlive = false;
	double spawnTimer = 0;
	sf::Vector2f baseSize = sf::Vector2f(32, 32);
	Player() {}
	Player(Game* g);
	bool BombAvailable();

	void UpdateEntity(double dt);
	void SpawnPlayer(double dt);
	void KillPlayer();
	void LoadSave(int& _dmgLvl, int& _asLvl, int& savedBomb) {
		damageLevel = _dmgLvl;
		damage += damageLevel;
		attackSpeedLevel = _asLvl;
		for (int i = 1; i <= attackSpeedLevel; i++) {
			attackSpeed -= 0.025 * pow(0.85, attackSpeedLevel);
		}
		bomb = savedBomb;
	}
};

