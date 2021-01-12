#include "Button.hpp"
#include "HUD.hpp"


Button::Button(std::string path, sf::Vector2f pos, bool isVis)
{
	idleTex.loadFromFile(path + "idle.png");
	hoverTex.loadFromFile(path + "hover.png");
	buttonShape.setSize(sf::Vector2f(48, 48));
	buttonShape.setOrigin(24, 24);
	buttonShape.setPosition(pos);
	isVisible = isVis;
	buttonShape.setTexture(&idleTex);
}


void Button::UpdateButton(sf::Vector2f mousePos) {
	if (buttonShape.getGlobalBounds().contains(mousePos)) {
		mouseHover(true);
	}
	else {
		mouseHover(false);
	}
}



