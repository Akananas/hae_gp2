#pragma once
#include "Button.hpp"
#include "SFML/Graphics.hpp"
class Game;
class HUD : public sf::Drawable
{
public:
	Game* game;
	Button testButton;
	HUD(){}
	HUD(Game* g);

	Button* CheckButton() {
		if (testButton.isHovering) {
			return &testButton;
		}
		return nullptr;
	}

	void Update(sf::Vector2f mousePos) {
		testButton.UpdateButton(mousePos);

	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(testButton, states);
	}
};

