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
	sf::Text musicCredit;
	bool optionOpen =false;
	sf::RectangleShape cursorPos;
	sf::RectangleShape coinsIcon;
	sf::RectangleShape bombButton;
	Button optionButton;
	Button closeButton;
	Button quitButton;
	Slider sfxSlider;
	Slider musicSlider;
	HUD(){}
	HUD(Game* g);

	void CheckButton();

	void Update(sf::Vector2f mousePos, double dt);
	void UpdateBombText(int* bomb);
	void LevelUp();
	void CheckSlider();
	bool ButtonHovered();
	void OpenOption() {
		ChangeMenuVisibility(true);
	}
	void CloseOption() {
		ChangeMenuVisibility(false);
	}
	void SetData();
private:
	void ChangeMenuVisibility(bool val);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

