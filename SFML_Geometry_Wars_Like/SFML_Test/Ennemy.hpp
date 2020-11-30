#pragma once
#include "Entity.hpp"

class Ennemy : public Entity{
public:
	float hp;
	float speed = 5.0;
	Ennemy() {
		hp = 5;
	}
	Ennemy(Game* g, float x, float y) {
		this->game = g;
		sprite.setSize(sf::Vector2f(32, 32));
		sprite.setOrigin(sf::Vector2f(16, 16));
		sprite.setFillColor(sf::Color::Red);
		radius = 16;
		hp = 5;
		SetPosition(x, y);
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
	void UpdateEntity(double dt, sf::Vector2i& playerPos);

};

