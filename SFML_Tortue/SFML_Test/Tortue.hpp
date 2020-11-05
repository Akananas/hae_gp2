#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Tortue : public sf::Drawable{
public:
	sf::CircleShape tortue;
	sf::RectangleShape direction;
	float pixelToMove = 0;
	float nextRotate = 0;
	float speed = 5;
	float rotSpeed = 2.5f;
	Tortue(){
		tortue.setRadius(25);
		tortue.setFillColor(sf::Color::Green);
		tortue.setOrigin(25, 25);
		tortue.setPosition(300, 300);
		direction.setSize(sf::Vector2f(50, 8));
		direction.setOrigin(0, 4);
		direction.setPosition(tortue.getPosition());
		direction.setRotation(tortue.getRotation());
	}
	bool GetNextMove() {
		if (pixelToMove <= 0 && nextRotate == 0) {
			return true;
		}
		return false;
	}
	void RotateTortue(float angle, double dt);

	void Move(double dt, int side);


	sf::Vector2f rotateVector(sf::Vector2f pos) {
		float angle = tortue.getRotation() * (3.14159 / 180.0);
		sf::Vector2f dir(cos(angle), sin(angle));
		return dir;
	}


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(tortue, states);
		target.draw(direction, states);
	}
};