#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
class Stars : public sf::Drawable {
public:
	Stars():
		_stars(1500),
		starsVertex(sf::Points, 1500) 
	{
		for (std::size_t i = 0; i < _stars.size(); i++) {
			_stars[i].velMul = 1 + rand() % 4;
			starsVertex[i].position = sf::Vector2f(-640 + rand() % 2560, -360 + rand() % 1440);
		}
	}
	void UpdateStars(double& dt, sf::Vector2f vel) {
		for (std::size_t i = 0; i < _stars.size(); i++) {
			starsVertex[i].position -= speed * (float)Entity::GRID_SIZE * vel * _stars[i].velMul * (float)dt;
		}
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the vertex array
		target.draw(starsVertex, states);
	}
	struct Star {
		float velMul;
	};
	float speed = 5;
	std::vector<Star> _stars;
	sf::VertexArray starsVertex;
};