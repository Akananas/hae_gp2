#pragma once
#include "Entity.hpp"
class Bullet : public Entity {
public:
	Bullet(Game* g, sf::Vector2f spawnPos, sf::Vector2f dir) {
		dx = dir.x;
		dy = dir.y;
		sprite.setSize(sf::Vector2f(8, 8));
		sprite.setOrigin(sf::Vector2f(4, 4));
		sprite.setFillColor(sf::Color::Yellow);
		SetPosition(spawnPos);
		radius = 4;
		game = g;
	}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Bullet*>(type)) {
			return true;
		}
		return false;
	}
	void UpdateEntity(double dt) {
		MoveX();
		MoveY();
		SetSpriteCoor();
	}

	void MoveY();
	void MoveX();
};

