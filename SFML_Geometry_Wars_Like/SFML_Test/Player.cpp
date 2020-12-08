#include "Player.hpp"

bool Player::BombAvailable() {
	if (bomb > 0) {
		return true;
	}
	return false;
}

void Player::UpdateEntity(double dt) {
	if (isAlive) {
		Entity::UpdateEntity(dt);
		float friction = 1.0f / (1 + 10.f * float(dt));
		dx *= friction;
		dy *= friction;
	}
	else {
		SpawnPlayer(dt);
	}
}

void Player::SpawnPlayer(double dt) {
	if (spawnTimer >= 0.75) {
		isAlive = true;

	}
	else {
		spawnTimer += dt;
		sprite.setScale(sf::Vector2f(spawnTimer / 0.75, spawnTimer / 0.75));
	}
}
