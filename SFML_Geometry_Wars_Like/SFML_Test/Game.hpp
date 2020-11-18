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
#include "Particle.hpp"
class HotReloadShader;

class Game {
public:

	sf::RenderWindow* win;
	Player player;
	sf::RectangleShape  bg;
	HotReloadShader *bgShader = nullptr;
	sf::Texture			tex;
	std::vector<Entity*> ennemy;
	std::vector<Bullet> bullet;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;
	std::vector<Particle> particleManager;
	Game(sf::RenderWindow* win);
	sf::View curView;

	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {

			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
			sf::Vector2f mouseWorld = win->mapPixelToCoords(mousePos);
			sf::Vector2f dir = mouseWorld - player.GetPosition();
			sf::Vector2f normalized(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
			bullet.push_back(Bullet(this, player.GetPosition(), normalized));
		}
	}

	void pollInput(double dt) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			player.dx = -0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(this,player.sprite.getPosition(),sf::Vector2f(0,0), sf::Color(86, 61, 245),0.5));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.dx = 0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(this, player.sprite.getPosition(),sf::Vector2f(0, 0), sf::Color(86, 61, 245), 0.5));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			player.dy = -0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(this, player.sprite.getPosition(), sf::Vector2f(0, 0), sf::Color(86, 61, 245), 0.5));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.dy = 0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(this, player.sprite.getPosition(), sf::Vector2f(0, 0), sf::Color(86, 61, 245), 0.5));
			}
		}
	}

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
	void draw();
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
};