#pragma once
#include "Scene.hpp"
#include "FastEnemy.hpp"
#include "SlowEnemy.hpp"
#include "RotateEnemy.hpp"
#include "Boss.hpp"
class GameScene : public Scene {
public:
	std::vector<Enemy*> enemy;
	TextValue* val = nullptr;
	float levelTimer = 0;
	float nextSpawnTimer = 0;
	GameScene(Game* g) {
		game = g;
		val = &game->textVal;
	}
	void InitScene();
	void UpdateScene(double dt);
	void ProcessInput(sf::Event& event);
private:
	int BombDamage(float& bombRa);
	sf::Vector2f FindSpawn();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

