#include "Button.hpp"

void Button::mouseHover(bool hovering) {
	if (hovering) {
		buttonShape.setTexture(&hoverTex);
	}
	else {
		buttonShape.setTexture(&idleTex);
	}
	isHovering = hovering;
}

Button::Button(std::string path, sf::Vector2f pos, std::function<void()> function) {
	idleTex.loadFromFile(path + "idle.png");
	hoverTex.loadFromFile(path + "hover.png");
	clickedTex.loadFromFile(path + "clicked.png");
	buttonShape.setSize(sf::Vector2f(48, 48));
	buttonShape.setOrigin(24, 24);
	buttonShape.setPosition(pos);
	onClick = function;
}

void Button::SetTexture() {
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
