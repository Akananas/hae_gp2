#pragma once
#include "Scene.hpp"
class GameScene :
    public Scene
{
public:
	std::vector<Enemy*> enemy;
	float levelTimer = 0;
	float nextSpawnTimer = 0;
	GameScene(Game* g) {
		game = g;
	}
	void InitScene();
	void UpdateScene(double dt);
	void ProcessInput(sf::Event& event);
	int BombDamage(float& bombRa);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = enemy.size() - 1; i >= 0; i--) {
			target.draw(*enemy[i],states);
		}
	}
};

