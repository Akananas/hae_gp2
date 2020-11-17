#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class Particle : public Entity{
public:
	float life = 1.0;
	Particle(Game* g, sf::Vector2f spawnPos, sf::Vector2f speed, sf::Color color) {
		dx = speed.x;
		dy = speed.y;
		sprite.setSize(sf::Vector2f(8, 8));
		sprite.setOrigin(sf::Vector2f(4, 4));
		sprite.setFillColor(color);
		SetPosition(spawnPos);
		radius = 4;
		game = g;
	}
	~Particle() {}
	bool CheckType(Entity* type) {
		if (dynamic_cast<Particle*>(type)) {
			return true;
		}
		return false;
	}
	void UpdateEntity(double dt) {
		MoveX();
		MoveY();
		SetSpriteCoor();
		life -= dt;
		if (life < 0) {
			destroyed = true;
		}
	}
	void MoveY();
	void MoveX();
};