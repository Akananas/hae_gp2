#include "HUD.hpp"
#include "Game.hpp"
HUD::HUD(Game* g) {
	game = g;
	testButton = Button("../res/Option/", sf::Vector2f(40, 40), std::bind(&Game::StartGame, game));
	testButton.SetTexture();
}
