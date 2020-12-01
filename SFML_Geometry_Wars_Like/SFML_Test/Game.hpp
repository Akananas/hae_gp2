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
#include "MenuObject.hpp"
#include "Ennemy.hpp"
#include "FloatingText.hpp"


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
	std::vector<MenuObject> menuObject;
	std::vector<FloatingText> floatingText;
	sf::View curView;
	int level = 1;
	int money = 0;
	int score = 0;
	float shootCooldown = 0.2f;
	sf::Font moneyFont;
	sf::Text moneyText;
	sf::Text scoreText;
	bool playing = false;

	Game(sf::RenderWindow* win);



	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				StartGame();
			}
			if (event.key.code == sf::Keyboard::E) {
				if (player.BombAvailable() && playing) {
					float bombRa = player.bombRadius;
					int bombChain = 0;
					for (int i = ennemy.size()-1; i >= 0; i--) {
						sf::Vector2f dis = ennemy[i].GetPosition() - player.GetPosition();
						float mag = Entity::getMag(dis);
						if (mag <= bombRa) {
							particleManager.push_back(ParticleSystem(400, sf::Color(118, 5, 72), ennemy[i].GetPosition(), false, 250, 1.5f));
							ennemy.erase(ennemy.begin() + i);
							money += 5 + bombChain;
							score += 50 * (bombChain+1);
							bombChain++;
						}
					}
					if (bombChain > 1) {
						FloatingText bombText("Bomb Chain: " + std::to_string(bombChain), moneyFont, player.GetPosition(), sf::Color(255, 166, 158));
						floatingText.push_back(bombText);
					}
					player.bomb--;
				}
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
	void CreateWall(sf::Vector2i& w);
	void drawGame();
	void drawUI();
	void PlayerView() {
		curView.setCenter(player.GetPosition());
		win->setView(curView);
	}
	bool isWall(float cx, float cy);
	void StartGame() {
		level = 1;
		playing = true;
		player.KillPlayer();
		for (int i = 0; i < 20; i++) {
			ennemy.push_back(Ennemy(this, 20 + (rand() % 1220), 20 + (rand() % 660), sf::Color(134, 91, 111)));
		}
	}
	void StartMenu() {
		playing = false;
		player.SetPosition(sf::Vector2f(640, 360));
	}
	void CreateMenu();
	void AddMoney(int _money) {
		money += _money;
	}
	void SwitchMenu(MenuState val, int& index);
};
