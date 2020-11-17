#pragma once
#include "Entity.hpp"

class Player :public Entity {
public:
	Player() {}
	Player(Game* g) {
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		radius = 16;
		game = g;
	}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Player*>(type)) {
			return true;
		}
		return false;
	}
	void UpdateEntity(double dt) {
		Entity::UpdateEntity(dt);
		dx *= 0.5;
		dy *= 0.5;
	}
};

