#pragma once
#include "Entity.hpp"
class Ennemy : public Entity
{
public:
	Ennemy() {
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(sf::Color::Red);
		radius = 16;
	}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Ennemy*>(type)) {
			return true;
		}
		return false;
	}
};

