#include "Stars.hpp"

void Stars::UpdateStars(double& dt, sf::Vector2f vel) {
	for (std::size_t i = 0; i < _stars.size(); i++) {
		starsVertex[i].position -= speed * (float)Entity::GRID_SIZE * vel * _stars[i].velMul * (float)dt;
	}
}

void Stars::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw the vertex array
	target.draw(starsVertex, states);
}
