#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
class Button : public sf::Drawable{
public:
	sf::Texture idleTex;
	sf::Texture hoverTex;
	sf::Texture clickedTex;
	sf::RectangleShape buttonShape;
	bool isHovering = false;
	std::function<void()> onClick;
	Button(){}
	Button(std::string path, sf::Vector2f pos, std::function<void()> function) {
		idleTex.loadFromFile(path + "idle.png");
		hoverTex.loadFromFile(path + "hover.png");
		clickedTex.loadFromFile(path + "clicked.png");
		buttonShape.setSize(sf::Vector2f(48, 48));
		buttonShape.setOrigin(24, 24);
		buttonShape.setPosition(pos);
		onClick = function;
	}
	void SetTexture() {
		buttonShape.setTexture(&idleTex);
	}
	void UpdateButton(sf::Vector2f mousePos) {
		if (buttonShape.getGlobalBounds().contains(mousePos)) {
			mouseHover(true);
		}
		else {
			mouseHover(false);
		}
	}
	void mouseHover(bool hovering) {
		if (hovering) {
			buttonShape.setTexture(&hoverTex);
		}
		else {
			buttonShape.setTexture(&idleTex);
		}
		isHovering = hovering;
	}

	void mouseClick() {
		buttonShape.setTexture(&clickedTex);
		onClick();
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(buttonShape, states);
	}
};

