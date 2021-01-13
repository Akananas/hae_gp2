#pragma once
#include "Button.hpp"
#include "Slider.hpp"
#include "SFML/Graphics.hpp"
class Game;
class TextValue;
class HUD : public sf::Drawable{
public:
	Game* game = nullptr;
	TextValue* val = nullptr;
	sf::Font* font = nullptr;
	sf::Texture cursor;
	sf::Font gameFont;
	sf::Text moneyText;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text bombText;
	sf::Text fpsText;
	bool optionOpen =false;
	sf::RectangleShape cursorPos;
	Button optionButton;
	Button closeButton;
	Slider sfxSlider;
	HUD(){}
	HUD(Game* g);

	void CheckButton();

	void Update(sf::Vector2f mousePos, double dt);
	void UpdateBombText(int* bomb);
	void LevelUp();
	void CheckSlider();
	bool ButtonHovered() {
		if (optionButton.isClickable() || closeButton.isClickable() || sfxSlider.isClickable()) {
			return true;
		}
		return false;
	}
	void OptionMenu() {
		if (optionOpen) {
			optionOpen = false;
			optionButton.isVisible = true;
			closeButton.isVisible = false;
			sfxSlider.isVisible = false;
		}
		else {
			optionOpen = true;
			closeButton.isVisible = true;
			optionButton.isVisible = false;
			sfxSlider.isVisible = true;

		}
	}

	void SetCursorTexture() {
		cursorPos.setTexture(&cursor);
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(fpsText, states);
		target.draw(moneyText, states);
		target.draw(scoreText, states);
		target.draw(levelText, states);
		target.draw(bombText, states);
		if (optionOpen) {
			target.draw(closeButton, states);
			target.draw(sfxSlider, states);
		}
		else {
			target.draw(optionButton, states);
		}
		target.draw(cursorPos, states);

	}
};

