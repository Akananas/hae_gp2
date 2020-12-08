#include "MenuScene.hpp"

MenuScene::MenuScene(Game* g) {
	game = g;
}

void MenuScene::InitScene() {
	if (menuObject.size() == 0) {
		CreateMenu();
	}
	for (auto menu : menuObject) {
		menu.StartSpawn();
	}
}

void MenuScene::UpdateScene(double dt) {
	for (int i = menuObject.size() - 1; i >= 0; i--) {
		menuObject[i].UpdateEntity(dt);
		if (game->player.overlaps(menuObject[i])) {
			game->player.Pushback(menuObject[i]);
		}
	}
	for (int i = game->bullet.size() - 1; i >= 0; i--) {
		game->bullet[i].UpdateEntity(dt);
		for (int j = menuObject.size() - 1; j >= 0; j--) {
			if (game->bullet[i].overlaps(menuObject[j])) {
				game->bullet[i].destroyed = true;
				game->bullet[i].explosionColor = menuObject[j].sprite.getFillColor();
				game->SwitchMenu(menuObject[j], j);
			}
		}
	}
}

void MenuScene::ProcessInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			game->StartGame();
		}
	}
}

void MenuScene::CreateMenu() {
	MenuObject start(StartState, sf::Color(71, 191, 255), sf::Vector2f(640, 620), game->moneyFont, false);
	MenuObject powerUp(PowerUpState, sf::Color(134, 91, 111), sf::Vector2f(320, 120), game->moneyFont, true, 5 * game->player.damageLevel);
	MenuObject attackSpeedUp(AttackSpeedState, sf::Color(143, 57, 133), sf::Vector2f(640, 120), game->moneyFont, true, 5 * game->player.attackSpeedLevel);
	MenuObject BombBuy(BombState, sf::Color(118, 5, 72), sf::Vector2f(910, 120), game->moneyFont, true, 50);
	menuObject.push_back(start);
	menuObject.push_back(powerUp);
	menuObject.push_back(attackSpeedUp);
	menuObject.push_back(BombBuy);
	maxLevelText.setFont(game->moneyFont);
	maxLevelText.setCharacterSize(24);
	maxLevelText.setString("Highest Level: " + std::to_string(game->maxLevel));
	sf::FloatRect textBounds = maxLevelText.getLocalBounds();
	maxLevelText.setPosition(sf::Vector2f(400 - textBounds.width / 2.0, 604));
	highScoreText.setFont(game->moneyFont);
	highScoreText.setCharacterSize(24);
	highScoreText.setString("Highscore: " + std::to_string(game->highScore));
	textBounds = highScoreText.getLocalBounds();
	highScoreText.setPosition(sf::Vector2f(860 - textBounds.width / 2.0, 604));
}
