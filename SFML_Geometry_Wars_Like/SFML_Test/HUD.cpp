#include "HUD.hpp"
#include "Game.hpp"
#include <iostream>
HUD::HUD(Game* g) {
	game = g;
	val = &game->textVal;
	font = &game->gameFont;
	optionOpen = false;
	//optionButton = Button("../res/Option/", sf::Vector2f(40, 40), std::bind(&Game::StartGame, game));
	optionButton = Button("../res/Option/", sf::Vector2f(40, 40), true);
	closeButton = Button("../res/Close/", sf::Vector2f(40, 40), false);
	if (cursor.loadFromFile("../res/crossair_white.png")) {
		cursorPos.setSize(sf::Vector2f(32, 32));
		cursorPos.setOrigin(16, 16);
		cursorPos.setTexture(&cursor);
	}
	moneyText.setFont(*font);
	moneyText.setCharacterSize(24);
	moneyText.setPosition(1200, 20);
	moneyText.setFillColor(sf::Color::White);

	scoreText.setFont(*font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(sf::Vector2f(640, 20));
	scoreText.setFillColor(sf::Color::White);

	levelText.setFont(*font);
	levelText.setCharacterSize(24);
	levelText.setString("Level: " + std::to_string(val->level));
	levelText.setPosition(sf::Vector2f(340, 20));

	fpsText.setFont(*font);
	fpsText.setCharacterSize(24);
	fpsText.setPosition(sf::Vector2f(60, 20));




	bombText.setFont(*font);
	bombText.setCharacterSize(24);
	bombText.setPosition(sf::Vector2f(640, 50));
	bombText.setFillColor(sf::Color::White);

};

void HUD::Update(sf::Vector2f mousePos, double dt) {
	optionButton.UpdateButton(mousePos);
	closeButton.UpdateButton(mousePos);
	cursorPos.setPosition(mousePos);
	scoreText.setString("SCORE: " + std::to_string(val->score));
	moneyText.setString(std::to_string(val->money));
	sf::FloatRect textBounds = moneyText.getLocalBounds();
	moneyText.setPosition(sf::Vector2f(1200 - textBounds.width / 2.0, 20));
	fpsText.setString("FPS: " + std::to_string((int)(1 / dt)));
}

void HUD::UpdateBombText(int* bomb) {
	bombText.setString("Bomb: " + std::to_string(*bomb));
}

void HUD::LevelUp() {
	levelText.setString("Level: " + std::to_string(val->level));
}
