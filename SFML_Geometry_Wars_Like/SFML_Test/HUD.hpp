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
	sf::RectangleShape cursorPos;
	Button testButton;
	HUD(){}
	HUD(Game* g);

	Button* CheckButton() {
		if (testButton.isHovering) {
			return &testButton;
		}
		return nullptr;
	}

	void Update(sf::Vector2f mousePos, double dt);
	void UpdateBombText(int* bomb);
	void LevelUp();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(fpsText, states);
		target.draw(moneyText, states);
		target.draw(scoreText, states);
		target.draw(levelText, states);
		target.draw(bombText, states);
		target.draw(testButton, states);
		target.draw(cursorPos, states);

	}
};

