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
	sf::Text sliderName;
	int minPosX, maxPosX = 0;
	bool isVisible = false;
	bool hovering = false;
	Slider(){}
	Slider(SliderEffect _se, sf::Vector2f pos, sf::Font* font, std::string _textString, float val) {
		sliderEffect = _se;
		background.setSize(sf::Vector2f(256, 36));
		background.setOrigin(128, 18);
		background.setPosition(pos);
		background.setFillColor(sf::Color(125, 125, 125));
		moveableShape.setSize(sf::Vector2f(36, 36));
		moveableShape.setOrigin(18, 18);
		minPosX = background.getPosition().x - (256 / 2) + 18;
		maxPosX = background.getPosition().x + (256 / 2) - 18;
		moveableShape.setPosition(sf::Vector2f(minPosX + val * (maxPosX - minPosX), pos.y));
		moveableShape.setFillColor(sf::Color::Red);
		sliderName.setFont(*font);
		sliderName.setCharacterSize(18);
		sliderName.setString(_textString);
		sf::FloatRect textBounds = sliderName.getLocalBounds();
		sliderName.setPosition(sf::Vector2f(pos.x - textBounds.width / 2.0, pos.y - 56));
	}
	float GetValue() {
		return (moveableShape.getPosition().x - minPosX) / (256 - 36);
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
		return GetValue();
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
		target.draw(sliderName, states);
	}
};

