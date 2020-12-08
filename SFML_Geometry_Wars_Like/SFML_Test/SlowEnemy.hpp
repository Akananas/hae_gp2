#pragma once
#include "Enemy.hpp"
class SlowEnemy : public Enemy
{
public:
	SlowEnemy(Game* g, int level, float x, float y, sf::Color _col);
	SlowEnemy(Game* g, int level, sf::Vector2f spawn, sf::Color _col);
};



