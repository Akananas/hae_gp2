#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "ParticleSystem.hpp"
#include "MenuObject.hpp"
#include "Stars.hpp"
#include "FastEnemy.hpp"
#include "SlowEnemy.hpp"
#include "RotateEnemy.hpp"
#include "FloatingText.hpp"
#include "Scene.hpp"


class HotReloadShader;
class Enemy;
class Scene;
class Game {
public:
	static const int cols = 1280 / Entity::GRID_SIZE;
	static const int lastLine = 720 / Entity::GRID_SIZE;
	sf::RenderWindow* win = nullptr;
	Player player;
	std::vector<Bullet> bullet;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;
	std::vector<ParticleSystem> particleManager;
	std::vector<FloatingText> floatingText;
	sf::View curView;
	int level = 1;
	int money = 0;
	int score = 0;
	float shootCooldown = 0.2f;
	Stars stars;
	sf::Font moneyFont;
	sf::Text moneyText;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text bombText;
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

	Scene* curScene = nullptr;

	Game(sf::RenderWindow* win);

	void processInput(sf::Event event);

	void pollInput(double dt);

	void Update(double deltaTime);

	void cacheWall();
	void CreateWall(sf::Vector2i& w);
	bool isWall(float cx, float cy);

	void StartMenu();
	void StartGame();

	void SwitchMenu(MenuObject& val, int& index);
	void UpdateBombText();
	void AddMoney(int _money);
	void UpgradeLevel();

	void PlayerView();
	void drawGame();
	void drawUI();
};
