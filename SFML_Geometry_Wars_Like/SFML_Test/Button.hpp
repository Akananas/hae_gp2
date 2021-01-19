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
	std::function<void()> onClick;
	Button(){}
	Button(std::string path, sf::Vector2f pos, sf::Vector2f size,bool isVis);
	void UpdateButton(sf::Vector2f mousePos);
	void SetOnClick(std::function<void()> function) {
		onClick = function;
	}
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
	bool isClickable() {
		if (isHovering && isVisible) {
			return true;
		}
		return false;
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(buttonShape, states);
	}
};

