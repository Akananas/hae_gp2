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
#include "FloatingText.hpp"
#include "Scene.hpp"
#include "HUD.hpp"
struct SaveFile {
	int Highscore = 0;
	int MaxLevel = 0;
	int savedMoney = 0;
	int savedBomb = 3;
	int savedDamageLevel = 1;
	int savedAttackSpeedLevel = 1;
	float sfxVolume = 1.f;
	float musicVolume = 1.f;
};
struct TextValue {
	int level = 1;
	int money = 0;
	int score = 0;
};
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
	int highScore = 0;
	int maxLevel = 1;

	float shootCooldown = 0.2f;
	Stars stars;
	sf::Font gameFont;
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
	sf::Music bgm;
	HotReloadShader* chargeAttack = nullptr;
	TextValue textVal;
	HotReloadShader* shockwave = nullptr;
	sf::Texture winTex;
	sf::Texture noise;
	bool respawn;
	float respawnTimer = 0.0f;
	float shootTimer = 0.0f;
	Scene* curScene = nullptr;
	HUD hud;
	Game(sf::RenderWindow* win);

	void processInput(sf::Event event);

	void pollInput(double dt);

	void Update(double deltaTime);
	void cacheWall();
	void CreateWall(sf::Vector2i& w);
	bool isWall(float cx, float cy);

	void StartMenu();
	void StartGame();
	void StartRespawn() {
		respawn = true;
		respawnTimer = 0;
	}

	void SwitchMenu(MenuObject& val, int& index);
	void AddMoney(int _money);
	void UpgradeLevel();
	void ChangeVolume(float val, SliderEffect effect) {
		if (effect == SFX) {
			attackSound.setVolume(5 * val);
			hitSound.setVolume(15 * val);
			explosionSound.setVolume(15 * val);
			bombSound.setVolume(15 * val);
			powerUpSound.setVolume(15 * val);
		}
		else if (effect == Music) {
			bgm.setVolume(15 * val);
		}
	}
	void PlayerView();
	void drawGame();
	void drawUI();
	void Shoot();
	void CheckHighscore();


	SaveFile curSave;

	SaveFile ReadSaveFile();

	void SaveGame();
};
