#pragma once
#include "Button.hpp"
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
	std::vector<Button*> buttonList;
	HUD(){}
	HUD(Game* g);

	void CheckButton() {
		if (optionButton.isHovering || closeButton.isHovering) {
			OptionMenu();
		}
	}

	void Update(sf::Vector2f mousePos, double dt);
	void UpdateBombText(int* bomb);
	void LevelUp();
	bool ButtonHovered() {
		if (optionButton.isHovering) {
			return true;
		}
		if (closeButton.isHovering ) {
			return true;
		}
		return false;
	}
	void OptionMenu() {
		if (optionOpen) {
			optionOpen = false;
			optionButton.isVisible = true;
			closeButton.isVisible = false;
		}
		else {
			optionOpen = true;
			closeButton.isVisible = true;
			optionButton.isVisible = false;
		}
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
		}
		else {
			target.draw(optionButton, states);
		}
		target.draw(cursorPos, states);

	}
};

