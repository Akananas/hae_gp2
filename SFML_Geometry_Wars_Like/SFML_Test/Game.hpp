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
#include "Stars.hpp"
#include "Ennemy.hpp"
#include "FastEnnemy.hpp"
#include "SlowEnnemy.hpp"
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
	std::vector<Ennemy*> ennemy;
	std::vector<Bullet> bullet;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;
	std::vector<ParticleSystem> particleManager;
	std::vector<MenuObject> menuObject;
	std::vector<FloatingText> floatingText;
	sf::View curView;
	int level = 1;
	float levelTimer = 0;
	float nextSpawnTimer = 0;
	int money = 0;
	int score = 0;
	float shootCooldown = 0.2f;
	Stars stars;
	sf::Font moneyFont;
	sf::Text moneyText;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text fpsText;
	sf::SoundBuffer attackSoundBuffer;
	sf::Sound attackSound;
	sf::SoundBuffer powerUpSoundBuffer;
	sf::Sound powerUpSound;
	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;
	sf::SoundBuffer explosionSoundBuffer;
	sf::Sound explosionSound;
	sf::SoundBuffer bombSoundBuffer;
	sf::Sound bombSound;
	bool playing = false;

	Game(sf::RenderWindow* win);



	void processInput(sf::Event event);

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
		levelTimer = 0;
		playing = true;
		player.KillPlayer();
		levelText.setString("Level: " + std::to_string(level));
		/*for (int i = 0; i < 20; i++) {
			ennemy.push_back(Ennemy(this, 20 + (rand() % 1220), 20 + (rand() % 660), sf::Color(134, 91, 111)));
		}*/
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
