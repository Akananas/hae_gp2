#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class Particle : public Entity{
public:
	float life = 1.0;
	Particle(Game* g, sf::Vector2f spawnPos, sf::Vector2f speed, sf::Color color, float maxLife = 1) {
		dx = speed.x;
		dy = speed.y;
		sprite.setSize(sf::Vector2f(6, 6));
		sprite.setOrigin(sf::Vector2f(3,3));
		sprite.setFillColor(color);
		SetPosition(spawnPos);
		radius = 4;
		life = maxLife;
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