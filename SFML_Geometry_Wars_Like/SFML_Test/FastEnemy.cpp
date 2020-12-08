#include "FastEnemy.hpp"

FastEnemy::FastEnemy(Game* g, int level, float x, float y, sf::Color _col) {
	this->game = g;
	sprite.setSize(sf::Vector2f(16, 16));
	sprite.setOrigin(sf::Vector2f(8, 8));
	sprite.setFillColor(_col);
	radius = 8;
	hp = 1 * level;
	SetPosition(x, y);
	canMove = false;
	spawnTime = 0;
	speed = 10.0;
}

FastEnemy::FastEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col) {
	this->game = g;
	sprite.setSize(sf::Vector2f(16, 16));
	sprite.setOrigin(sf::Vector2f(8, 8));
	sprite.setFillColor(_col);
	radius = 8;
	hp = 1 * level;
	SetPosition(spawn);
	canMove = false;
	spawnTime = 0;
	speed = 10.0;
}
