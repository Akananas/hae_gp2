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

void MenuScene::CreateMenu() {
	MenuObject start(StartState, sf::Color(71, 191, 255), sf::Vector2f(100, 120), game->moneyFont, false);
	MenuObject powerUp(PowerUpState, sf::Color(134, 91, 111), sf::Vector2f(260, 120), game->moneyFont, true);
	MenuObject attackSpeedUp(AttackSpeedState, sf::Color(143, 57, 133), sf::Vector2f(420, 120), game->moneyFont, true);
	MenuObject BombBuy(BombState, sf::Color(118, 5, 72), sf::Vector2f(580, 120), game->moneyFont, true, 50);
	menuObject.push_back(start);
	menuObject.push_back(powerUp);
	menuObject.push_back(attackSpeedUp);
	menuObject.push_back(BombBuy);
}
