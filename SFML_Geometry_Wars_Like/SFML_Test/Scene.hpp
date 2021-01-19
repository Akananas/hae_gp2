#pragma once
#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Scene : public sf::Drawable{
public:
	Game* game = nullptr;
	Scene(){}
	virtual void InitScene() = 0;
	virtual void UpdateScene(double dt) = 0;
	virtual void ProcessInput(sf::Event& event) = 0;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

