#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
class Button : public sf::Drawable{
public:
	sf::Texture idleTex;
	sf::Texture hoverTex;
	sf::RectangleShape buttonShape;
	bool isHovering = false;
	bool isVisible = false;
	Button(){}
	Button(std::string path, sf::Vector2f pos, bool isVis);
	void UpdateButton(sf::Vector2f mousePos);
	void mouseHover(bool hovering) {
		if (isVisible) {
			if (hovering) {
				buttonShape.setTexture(&hoverTex);
			}
			else {
				buttonShape.setTexture(&idleTex);
			}
			isHovering = hovering;
		}
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(buttonShape, states);
	}
};

