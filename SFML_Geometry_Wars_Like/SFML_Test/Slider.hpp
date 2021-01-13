#pragma once
#include "SFML/Graphics.hpp"
enum SliderEffect {
	Music,
	SFX
};
class Slider : public sf::Drawable{
public:
	SliderEffect sliderEffect;
	sf::RectangleShape background;
	sf::RectangleShape moveableShape;
	int minPosX, maxPosX = 0;
	bool isVisible = false;
	bool hovering = false;
	Slider(){}
	Slider(SliderEffect _se, sf::Vector2f pos) {
		sliderEffect = _se;
		background.setSize(sf::Vector2f(256, 36));
		background.setOrigin(128, 18);
		background.setPosition(pos);
		background.setFillColor(sf::Color(125, 125, 125));
		moveableShape.setSize(sf::Vector2f(36, 36));
		moveableShape.setOrigin(18, 18);
		minPosX = background.getPosition().x - (256 / 2) + 18;
		maxPosX = background.getPosition().x + (256 / 2) - 18;
		moveableShape.setPosition(sf::Vector2f(maxPosX, pos.y));
		moveableShape.setFillColor(sf::Color::Red);
	}

	float DragSlider(sf::Vector2f mousePos) {
		if (mousePos.x > maxPosX) {
			moveableShape.setPosition(sf::Vector2f(maxPosX, moveableShape.getPosition().y));
		}
		else if (mousePos.x < minPosX) {
			moveableShape.setPosition(sf::Vector2f(minPosX, moveableShape.getPosition().y));
		}
		else {
			moveableShape.setPosition(sf::Vector2f(mousePos.x, moveableShape.getPosition().y));
		}
		return (moveableShape.getPosition().x - minPosX) / (256 - 36);
	}
	void UpdateSlider(sf::Vector2f& mousePos) {
		if (moveableShape.getGlobalBounds().contains(mousePos) && isVisible) {
			hovering = true;;
		}
		else {
			hovering = false;
		}
	}
	bool isClickable() {
		if (hovering && isVisible) {
			return true;
		}
		return false;
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		target.draw(moveableShape, states);
	}
};

