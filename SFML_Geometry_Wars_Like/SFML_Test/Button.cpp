#include "Button.hpp"

void Button::mouseHover(Vector2f) {
	if (hovering) {
		buttonShape.setTexture(&hoverTex);
	}
	else {
		buttonShape.setTexture(&idleTex);
	}
	isHovering = hovering;
}

void Button::UpdateButton(sf::Vector2f mousePos) {
	if (buttonShape.getGlobalBounds().contains(mousePos)) {
		mouseHover(true);
	}
	else {
		mouseHover(false);
	}
}
