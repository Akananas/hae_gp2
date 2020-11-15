#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include <vector>
#include "Entity.hpp"
#include "Particle.hpp"
class HotReloadShader;

class Game {
public:

	sf::RenderWindow* win;
	Entity player;
	sf::RectangleShape  bg;
	HotReloadShader *bgShader = nullptr;
	sf::Texture			tex;
	std::vector<Entity> otherEntity;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;
	std::vector<Particle> particleManager;
	Game(sf::RenderWindow* win);
	sf::RenderTexture* destX = nullptr;
	sf::RenderTexture* destFinal = nullptr;
	sf::Texture winTex;
	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {

			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
			mousePos.x /= Entity::GRID_SIZE;
			mousePos.y /= Entity::GRID_SIZE;
			int index = checkWallAtMouse(mousePos);
			if (index == -1) {
				walls.push_back(mousePos);
				CreateWall(mousePos);
			}
			else {
				walls.erase(walls.begin() + index);
				wallsRender.erase(wallsRender.begin() + index);
			}
		}
	}

	void pollInput(double dt) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			player.dx = -0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(player.sprite.getPosition(),-50, sf::Color(86, 61, 245)));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.dx = 0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(player.sprite.getPosition(),-50, sf::Color(86, 61, 245)));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			if (player.jump()) {
				/*for (int i = 0; i < 25; i++) {
					particleManager.push_back(Particle(player.sprite.getPosition(), 100 + rand() % 20, sf::Color::Red));
				}*/
			}
		}
	}
	int checkWallAtMouse(sf::Vector2i pos) {
		for (int i = 0; i < walls.size(); i++) {
			if (walls[i].x == pos.x && walls[i].y == pos.y) {
				return i;
			}
		}
		return -1;
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
	bool isWall(float cx, float cy) {
		for (sf::Vector2i & w : walls) {
			if (cx == w.x && cy == w.y) {
				return true;
			}
		}
		return false;
	}
};
