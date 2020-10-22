#pragma once
#include "SFML/Graphics.hpp"
class Particles {
public:
	sf::Vector2f dir;
	sf::RectangleShape shape;
	float speed = 0.0;
	float currentLife = 0.0;
	float lifeTime = 0.0;
	sf::Vector2f baseSize;
	sf::Color baseColor;
	sf::Color lastColor;
	float lastSize;
	float alpha;
	Particles(sf::Vector2f pos, sf::Vector2f dir, float lifeTime, float speed, sf::Vector2f size, sf::Color color, float lastSize, float alpha) {
		shape.setSize(size);
		shape.setOrigin(2.5, 2.5);
		sf::Vector2f newDir = dir + sf::Vector2f((rand() % 100) ,(rand() % 100));
		sf::Vector2f normalized = sf::Vector2f(newDir.x / sqrt(newDir.x * newDir.x + newDir.y * newDir.y), newDir.y / sqrt(newDir.x * newDir.x + newDir.y * newDir.y));
		float dot = normalized.x * dir.x + normalized.y * dir.y;
		if (dot < 0) {
			normalized = -normalized;
		}
		shape.setPosition(pos);
		shape.setFillColor(color);
		this->dir = normalized;
		this->speed = speed;
		this->lifeTime = lifeTime;
		this->baseSize = size;
		this->lastSize = lastSize;
		this->baseColor = color;
		this->alpha = (color.a - (color.a * alpha)) / lifeTime;
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
		shape.setPosition(shape.getPosition() + (randDir * (speed * (float)(60.0 * dt))));
		float nextSizeScale = 1 + (lastSize * (currentLife / lifeTime));
		sf::Color tmp = shape.getFillColor();
		if(tmp.a > 10){ tmp.a -= alpha * dt; }
		shape.setFillColor(tmp);
		shape.setSize(baseSize * nextSizeScale );
		return false;
	}
 };