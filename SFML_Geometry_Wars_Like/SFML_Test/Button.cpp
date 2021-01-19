#include "Button.hpp"
#include "HUD.hpp"


Button::Button(std::string path, sf::Vector2f pos, sf::Vector2f size, bool isVis)
{
	idleTex.loadFromFile(path + "idle.png");
	hoverTex.loadFromFile(path + "hover.png");
	buttonShape.setSize(size);
	buttonShape.setOrigin(size.x/2.0f, size.y / 2.0f);
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



