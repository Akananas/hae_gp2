#include "SlowEnemy.hpp"

SlowEnemy::SlowEnemy(Game* g, int level, float x, float y, sf::Color _col) {
	this->game = g;
	sprite.setSize(sf::Vector2f(32, 32));
	sprite.setOrigin(sf::Vector2f(16, 16));
	sprite.setFillColor(_col);
	radius = 16;
	hp = 2 * level;
	SetPosition(x, y);
	canMove = false;
	spawnTime = 0;
	speed = 5.0;
}

SlowEnemy::SlowEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col) {
	this->game = g;
	sprite.setSize(sf::Vector2f(32, 32));
	sprite.setOrigin(sf::Vector2f(16, 16));
	sprite.setFillColor(_col);
	radius = 16;
	hp = 2 * level;
	SetPosition(spawn);
	canMove = false;
	spawnTime = 0;
	speed = 5.0;
}
