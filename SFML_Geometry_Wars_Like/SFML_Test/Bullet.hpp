#pragma once
#include "Entity.hpp"
class Bullet : public Entity {
public:
	sf::Color explosionColor = sf::Color(247, 249, 118);
	float damage = 0;
	Bullet(Game* g, sf::Vector2f spawnPos, sf::Vector2f dir, float playerDamage);
	void UpdateEntity(double dt);

	void MoveY();
	void MoveX();
};

