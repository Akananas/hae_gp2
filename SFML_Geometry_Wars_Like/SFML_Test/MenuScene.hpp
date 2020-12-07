#pragma once
#include "Scene.hpp"

class MenuScene : public Scene {
public:
	std::vector<MenuObject> menuObject;
	MenuScene(Game* g);
	void InitScene();;

	void UpdateScene(double dt);
	void ProcessInput(sf::Event& event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				game->StartGame();
			}
		}
	}

	void CreateMenu();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto menu : menuObject) {
			target.draw(menu, states);
		}
	}
};

