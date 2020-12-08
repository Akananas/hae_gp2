#pragma once
#include "Scene.hpp"

class MenuScene : public Scene {
public:
	std::vector<MenuObject> menuObject;
	sf::Text highScoreText;
	sf::Text maxLevelText;
	MenuScene(Game* g);
	void InitScene();;

	void UpdateScene(double dt);
	void ProcessInput(sf::Event& event);

	void CreateMenu();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto menu : menuObject) {
			target.draw(menu, states);
		}
		target.draw(highScoreText);
		target.draw(maxLevelText);
	}
};

