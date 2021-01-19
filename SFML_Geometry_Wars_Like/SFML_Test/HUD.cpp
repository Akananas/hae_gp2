#include "HUD.hpp"
#include "Game.hpp"
#include <iostream>
HUD::HUD(Game* g) {
	game = g;
	val = &game->textVal;
	font = &game->gameFont;
	optionOpen = false;
	sfxSlider = Slider(SFX, sf::Vector2f(640, 440), font, "SFX volume", game->curSave.sfxVolume);
	musicSlider = Slider(Music, sf::Vector2f(640, 340), font, "Music volume", game->curSave.musicVolume);
	//optionButton = Button("../res/Option/", sf::Vector2f(40, 40), std::bind(&Game::StartGame, game));
	optionButton = Button("../res/Option/", sf::Vector2f(30, 35), sf::Vector2f(48,48) , true);
	closeButton = Button("../res/Close/", sf::Vector2f(30, 35), sf::Vector2f(48, 48), false);
	quitButton = Button("../res/Quit/", sf::Vector2f(640, 540), sf::Vector2f(128, 36), false);
	if (cursor.loadFromFile("../res/crossair_white.png")) {
		cursorPos.setSize(sf::Vector2f(32, 32));
		cursorPos.setOrigin(16, 16);
		cursorPos.setTexture(&cursor);
	}
	if (bombTex.loadFromFile("../res/buttonBomb.png")) {
		bombButton.setSize(sf::Vector2f(35, 38));
		bombButton.setOrigin(18, 19);
		bombButton.setPosition(580, 677);
		bombButton.setTexture(&bombTex);
	}
	coinsIcon.setSize(sf::Vector2f(38, 35));
	coinsIcon.setOrigin(19, 18);
	coinsIcon.setPosition(1140, 35);
	coinsIcon.setTexture(&game->coinsTex);

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
	bombText.setPosition(sf::Vector2f(610, 660));
	bombText.setFillColor(sf::Color::White);
	
	musicCredit.setFont(*font);
	musicCredit.setCharacterSize(24);
	musicCredit.setFillColor(sf::Color::White);
	musicCredit.setString("               Music by Joth\n opengameart.org/users/joth");
	sf::FloatRect textBounds = musicCredit.getLocalBounds();
	musicCredit.setPosition(sf::Vector2f(640- textBounds.width / 2.0, 180));

}
void HUD::CheckButton() {
	if (optionButton.isClickable()) {
		optionButton.onClick();
	}
	else if (closeButton.isClickable()) {
		closeButton.onClick();
	}
	else if (quitButton.isClickable()) {
		quitButton.onClick();
	}
};

void HUD::Update(sf::Vector2f mousePos, double dt) {
	optionButton.UpdateButton(mousePos);
	closeButton.UpdateButton(mousePos);
	quitButton.UpdateButton(mousePos);
	sfxSlider.UpdateSlider(mousePos);
	musicSlider.UpdateSlider(mousePos);
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

void HUD::CheckSlider() {
	if (sfxSlider.isClickable()) {
		game->ChangeVolume(sfxSlider.DragSlider(sf::Vector2f(sf::Mouse::getPosition(*game->win))), SFX);
	}
	else if (musicSlider.isClickable()) {
		game->ChangeVolume(musicSlider.DragSlider(sf::Vector2f(sf::Mouse::getPosition(*game->win))), Music);
	}
}

bool HUD::ButtonHovered() {
	if (optionButton.isClickable() || closeButton.isClickable()
		|| sfxSlider.isClickable() || musicSlider.isClickable()) {
		return true;
	}
	return false;
}

void HUD::SetData() {
	closeButton.SetOnClick(std::bind(&HUD::CloseOption, this));
	optionButton.SetOnClick(std::bind(&HUD::OpenOption, this));
	quitButton.SetOnClick(std::bind(&Game::CloseGame, game));
	cursorPos.setTexture(&cursor);
	bombButton.setTexture(&bombTex);
}

void HUD::ChangeMenuVisibility(bool val) {
	optionOpen = val;
	closeButton.isVisible = val;
	sfxSlider.isVisible = val;
	musicSlider.isVisible = val;
	quitButton.isVisible = val;
	optionButton.isVisible = !val;
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(fpsText, states);
	target.draw(moneyText, states);
	target.draw(scoreText, states);
	target.draw(levelText, states);
	target.draw(bombText, states);
	target.draw(bombButton, states);
	target.draw(coinsIcon, states);
	if (optionOpen) {
		target.draw(closeButton, states);
		target.draw(sfxSlider, states);
		target.draw(musicSlider, states);
		target.draw(quitButton, states);
		target.draw(musicCredit, states);
	}
	else {
		target.draw(optionButton, states);
	}
	target.draw(cursorPos, states);

}
