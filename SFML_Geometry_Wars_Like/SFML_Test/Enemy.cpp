#include "Enemy.hpp"
#include <iostream> 
bool Enemy::getDamage(float dmg) {
	hp -= dmg;
	std::cout << hp << " " << dmg << std::endl;
	if (hp <= 0) {
		destroyed = true;
	}
	return destroyed;
}

bool Enemy::canHurtPlayer() {
	return canMove;
}

void Enemy::UpdateEntity(double dt, sf::Vector2i& playerPos) {
	if (canMove) {
		MoveEnemy(dt, playerPos);
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

void Enemy::MoveEnemy(double& dt, sf::Vector2i& playerPos) {
	sf::Vector2i curPos(cx, cy);
	sf::Vector2f dir(playerPos - curPos);
	dir = normalized(dir);
	dx = dir.x * speed * dt;
	dy = dir.y * speed * dt;
	Entity::UpdateEntity(dt);
}
