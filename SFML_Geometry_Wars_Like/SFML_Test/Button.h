#pragma once
#include "SFML/Graphics.hpp"
class Button{
public:
	sf::Texture idleTex;
	sf::Texture hoverTex;
	sf::Texture clickedTex;
	sf::RectangleShape buttonShape;
	Button(std::string path, sf::Vector2f pos) {
		idleTex.loadFromFile(path + "idle.png");
		hoverTex.loadFromFile(path + "hover.png");
		clickedTex.loadFromFile(path + "clicked.png");
		buttonShape.setTexture(&idleTex);
		buttonShape.setSize(sf::Vector2f(32, 32));
		buttonShape.setOrigin(16, 16);
	}
	void mouseHover(bool hovering) {
		if (hovering && buttonShape.getTexture() != &hoverTex) {
			buttonShape.setTexture(&hoverTex);
		}
		else if (buttonShape.getTexture() != &idleTex) {
			buttonShape.setTexture(&idleTex);
		}
	}

	void mouseClick() {
		buttonShape.setTexture(&clickedTex);
	}

};

