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
	sf::Texture bombTex;
	sf::Font gameFont;
	sf::Text moneyText;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text bombText;
	sf::Text fpsText;
	bool optionOpen =false;
	sf::RectangleShape cursorPos;
	sf::RectangleShape bombButton;
	Button optionButton;
	Button closeButton;
	Slider sfxSlider;
	Slider musicSlider;
	HUD(){}
	HUD(Game* g);

	void CheckButton();

	void Update(sf::Vector2f mousePos, double dt);
	void UpdateBombText(int* bomb);
	void LevelUp();
	void CheckSlider();
	bool ButtonHovered() {
		if (optionButton.isClickable() || closeButton.isClickable() 
			|| sfxSlider.isClickable() || musicSlider.isClickable()) {
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
			musicSlider.isVisible = false;
		}
		else {
			optionOpen = true;
			closeButton.isVisible = true;
			optionButton.isVisible = false;
			sfxSlider.isVisible = true;
			musicSlider.isVisible = true;
		}
	}

	void SetTexture() {
		cursorPos.setTexture(&cursor);
		bombButton.setTexture(&bombTex);
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(fpsText, states);
		target.draw(moneyText, states);
		target.draw(scoreText, states);
		target.draw(levelText, states);
		target.draw(bombText, states);
		target.draw(bombButton, states);
		if (optionOpen) {
			target.draw(closeButton, states);
			target.draw(sfxSlider, states);
			target.draw(musicSlider, states);
		}
		else {
			target.draw(optionButton, states);
		}
		target.draw(cursorPos, states);

	}
};

