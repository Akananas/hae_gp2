#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
class Stars : public sf::Drawable {
public:
	Stars():
		_stars(1000),
		starsVertex(sf::Points, 1000) 
	{
		for (std::size_t i = 0; i < _stars.size(); i++) {
			_stars[i].velMul = 1 + rand() % 4;
			starsVertex[i].position = sf::Vector2f(-640 + rand() % 2560, -360 + rand() % 1440);
		}
	}
	void UpdateStars(double& dt, sf::Vector2f vel);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	struct Star {
		float velMul;
	};
	float speed = 5;
	std::vector<Star> _stars;
	sf::VertexArray starsVertex;
};