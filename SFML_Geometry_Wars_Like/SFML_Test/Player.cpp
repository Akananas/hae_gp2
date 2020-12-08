#include "Player.hpp"

Player::Player(Game* g) {
	sprite.setSize(baseSize);
	sprite.setOrigin(sf::Vector2f(16, 16));
	sprite.setFillColor(sf::Color(
		200, 200, 200
	));
	radius = 16;
	game = g;
	damage = 1;
	attackSpeed = 0.2f;
	spawnTimer = 0;
}

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

void Player::KillPlayer() {
	dx = 0;
	dy = 0;
	spawnTimer = 0;
	isAlive = false;
	SetPosition(sf::Vector2f(640, 360));
}
