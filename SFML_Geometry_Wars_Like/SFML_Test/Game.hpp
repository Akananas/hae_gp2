#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include <vector>
#include "Entity.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "ParticleSystem.hpp"
#include "Ennemy.hpp"

class HotReloadShader;
class Ennemy;
class Game {
public:

	sf::RenderWindow* win;
	Player player;
	sf::RectangleShape  bg;
	HotReloadShader *bgShader = nullptr;
	sf::Texture			tex;
	std::vector<Ennemy> ennemy;
	std::vector<Bullet> bullet;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;
	std::vector<ParticleSystem> particleManager;
	sf::View curView;
	int level = 1;
	int money = 0;
	float shootCooldown = 0.2f;
	sf::Font moneyFont;
	sf::Text moneyText;
	Game(sf::RenderWindow* win);



	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				StartGame();
			}
		}
	}

	void pollInput(double dt);

	void Update(double deltaTime);
	void cacheWall() {
		wallsRender.clear();
		for (sf::Vector2i& w : walls) {
			CreateWall(w);
		}
	}
	void CreateWall(sf::Vector2i& w) {
		sf::RectangleShape rect(sf::Vector2f(16, 16));
		rect.setPosition(w.x * Entity::GRID_SIZE, w.y * Entity::GRID_SIZE);
		rect.setFillColor(sf::Color::Green);
		wallsRender.push_back(rect);
	}
	void drawGame();
	void drawUI();
	void PlayerView() {
		curView.setCenter(player.GetPosition());
		win->setView(curView);
	}
	bool isWall(float cx, float cy) {
		for (sf::Vector2i & w : walls) {
			if (cx == w.x && cy == w.y) {
				return true;
			}
		}
		return false;
	}
	void StartGame() {
		level = 1;
		player = Player(this);
		player.SetPosition(sf::Vector2f(640, 360));
		for (int i = 0; i < 20; i++) {
			ennemy.push_back(Ennemy(this, 20 + (rand() % 1220), 20 + (rand() % 660)));
		}
	}
};
