#include "Ennemy.hpp"

void Ennemy::UpdateEntity(double dt, sf::Vector2i& playerPos) {
	if (canMove) {
		sf::Vector2i curPos(cx, cy);
		sf::Vector2f dir(playerPos - curPos);
		dir = normalized(dir);
		dx = dir.x * speed * dt;
		dy = dir.y * speed * dt;
		Entity::UpdateEntity(dt);
	}
	else {
		if (spawnTime > 0.35) {
			canMove = true;
		}else{
			spawnTime += dt;
			sprite.setScale(sf::Vector2f(spawnTime  / 0.35, spawnTime / 0.35));
		}
	}
}
