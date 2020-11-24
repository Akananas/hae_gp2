#pragma once
#include "Entity.hpp"

class Ennemy : public Entity{
public:
	float hp;
	Ennemy() {
		hp = 5;
	}
	Ennemy(Game* g) {
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(sf::Color::Red);
		radius = 16;
		hp = 5;
	}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Ennemy*>(type)) {
			return true;
		}
		return false;
	}
	bool getDamage(float dmg) {
		hp -= dmg;
		if (hp <= 0) {
			destroyed = true;
		}
		return destroyed;
	}
};

