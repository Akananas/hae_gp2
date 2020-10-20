#pragma once
#include "SFML/Graphics.hpp"
class Particles {
public:
	sf::Vector2f dir;
	sf::RectangleShape shape;
	float speed = 0.0;
	float currentLife = 0.0;
	float lifeTime = 0.0;
	Particles(sf::Vector2f pos, sf::Vector2f dir, float lifeTime, float speed, sf::Vector2f size, sf::Color color) {
		shape.setSize(size);
		shape.setOrigin(2.5, 2.5);
		dir = dir + sf::Vector2f(rand() % 50, rand() % 50);
		sf::Vector2f normalized = sf::Vector2f(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
		shape.setPosition(pos);
		shape.setFillColor(color);
		this->dir = normalized;
		this->speed = speed;
		this->lifeTime = lifeTime;
	}
	~Particles() {
		//std::cout << "delete";
	}
	bool Update(double dt) {
		currentLife += dt;
		if (currentLife >= lifeTime) {
			return true;
		}
		sf::Vector2f randDir = dir * (float)(rand() % 5);
		shape.setPosition(shape.getPosition() + (randDir * speed * (float)(60.0 * dt)));
		return false;
	}
 };