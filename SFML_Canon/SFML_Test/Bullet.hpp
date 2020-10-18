#pragma once
#include "SFML/Graphics.hpp"
class Bullet {
public:
	sf::Vector2f dir;
	sf::CircleShape circle;
	float speed = 0.0;
	Bullet(sf::Vector2f pos, sf::Vector2f dir) {
		circle.setRadius(15);
		circle.setOrigin(15, 15);
		circle.setPosition(pos);
		circle.setFillColor(sf::Color::Cyan);
		this->dir = sf::Vector2f(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
		speed = 2.0;
	}
	~Bullet() {
		std::cout << "delete";
	}
	void Move() {
		circle.setPosition(circle.getPosition() + (dir * speed));
	}
	bool checkPos() {
		sf::Vector2f currentPos = circle.getPosition();
		if (currentPos.x > (1280 - circle.getRadius()) || currentPos.x < (0 + circle.getRadius())) {
			return true;
		}
		if (currentPos.y > (720 - circle.getRadius()) || currentPos.y < (0 + circle.getRadius())) {
			return true;
		}
		return false;
	}
};