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
	Button(std::string path, sf::Vector2f pos, std::function<void()> function);
	void SetTexture();
	void UpdateButton(sf::Vector2f mousePos);
	void mouseHover(bool hovering);

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

