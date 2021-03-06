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
#include "Pathfinding.hpp"
class HotReloadShader;
class Pathfinding;
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
	sf::VertexArray path;
	Pathfinding* pathfinding = nullptr;
	std::vector<sf::Vector2i> notWalls;
	void processInput(sf::Event event);

	void pollInput(double dt) {
		/*sf::Vector2f dir;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			dir.x += -0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(player.sprite.getPosition(),-50, sf::Color(86, 61, 245)));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			dir.x += 0.5f;
			for (int i = 0; i < 5; i++) {
				particleManager.push_back(Particle(player.sprite.getPosition(),-50, sf::Color(86, 61, 245)));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			dir.y -= 0.5f;
			particleManager.push_back(Particle(player.sprite.getPosition(), -50, sf::Color(86, 61, 245)));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			dir.y += 0.5f;
			particleManager.push_back(Particle(player.sprite.getPosition(), -50, sf::Color(86, 61, 245)));
		}
		if (dir != sf::Vector2f(0, 0)) {
			player.ChangeSpeed(dir.x, dir.y);
		}
		else {
			player.IdleState();
		}*/
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
