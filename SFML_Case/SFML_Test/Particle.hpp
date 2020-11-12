#pragma once
#include "SFML/Graphics.hpp"
class Particle : public sf::Drawable{
public:
	float life = 0.0;
	sf::RectangleShape _particle;
	float speed = -50;
	bool destroyed = false;
	Particle(sf::Vector2f pos, float speed, sf::Color col) {
		_particle.setSize(sf::Vector2f(8, 8));
		_particle.setFillColor(col);
		_particle.setOrigin(8, 8);
		sf::Vector2f randomVec(rand() % 10, rand() % 10);
		_particle.setPosition(pos + randomVec);
		this->speed = speed;
		life = 1;
	}

	void Update(double dt) {
		life -= dt;
		if (life <= 0) {
			destroyed = true;
		}
		sf::Vector2f pos = _particle.getPosition();
		pos.y += dt * speed;
		_particle.setPosition(pos);
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_particle, states);
	}
};