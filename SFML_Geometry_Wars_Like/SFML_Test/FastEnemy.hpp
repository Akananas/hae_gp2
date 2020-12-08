#pragma once
#include "Enemy.hpp"
class FastEnemy : public Enemy
{
public:
	FastEnemy(Game* g, int level, float x, float y, sf::Color _col);
	FastEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col);
};

