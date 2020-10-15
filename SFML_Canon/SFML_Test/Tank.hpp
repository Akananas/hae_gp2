#pragma once
#include "SFML\Graphics.hpp"
class Tank{
public:
	sf::Sprite sprite;
	Tank() {

	}
	void SetTank(sf::Texture text) {
		sprite.setTexture(text);
		sprite.setColor(sf::Color(255, 255, 255, 255));
		sprite.setPosition(500, 500);
		sprite.setOrigin(50, 50);
	}
	void RotateTank(float x) {
		sprite.setRotation(x);
	}
};

