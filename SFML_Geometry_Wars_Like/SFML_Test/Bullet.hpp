#pragma once
#include "Entity.hpp"
class Bullet : public Entity {
public:
	sf::Color explosionColor = sf::Color(247, 249, 118);
	Bullet(Game* g, sf::Vector2f spawnPos, sf::Vector2f dir);
	void UpdateEntity(double dt);

	void MoveY();
	void MoveX();
};

