#include "Ennemy.hpp"

void Ennemy::UpdateEntity(double dt, sf::Vector2i& playerPos) {
	sf::Vector2i curPos(cx, cy);
	sf::Vector2f dir(playerPos - curPos);
	dir = normalized(dir);
	dx = dir.x * speed * dt;
	dy = dir.y * speed * dt;
	Entity::UpdateEntity(dt);
}
