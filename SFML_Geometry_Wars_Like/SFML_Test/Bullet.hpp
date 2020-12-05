#pragma once
#include "Entity.hpp"
class Bullet : public Entity {
public:
	Bullet(Game* g, sf::Vector2f spawnPos, sf::Vector2f dir) {
		dx = dir.x;
		dy = dir.y;
		sprite.setSize(sf::Vector2f(8, 8));
		sprite.setOrigin(sf::Vector2f(4, 4));
		sprite.setFillColor(sf::Color(247, 249, 118));
		SetPosition(spawnPos);
		radius = 8;
		game = g;
	}
	void UpdateEntity(double dt);

	void MoveY();
	void MoveX();
};

