#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include <vector>
#include "Entity.hpp"

class Game {
public:
	sf::RenderWindow* win;
	Entity player;
	std::vector<Entity> otherEntity;
	std::vector<sf::Vector2i> walls;
	std::vector<sf::RectangleShape> wallsRender;

	Game(sf::RenderWindow* win) {
		this->win = win;
		player.SetPosition(win->getSize());
		Entity block;
		block.SetPosition(100, 100);
		otherEntity.push_back(block);
		int cols = 1280 / Entity::GRID_SIZE;
		int lastLine = 720 / Entity::GRID_SIZE - 1;
		for (int i = 0; i < cols; ++i) {
			walls.push_back(sf::Vector2i(i, lastLine));
		}
		for (int i = 0; i < lastLine; ++i) {
			walls.push_back(sf::Vector2i(0, i));
			walls.push_back(sf::Vector2i(cols - 1, i));
		}
		cacheWall();
	}

	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {

			}
		}
	}

	void pollInput(double dt) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			player.dx = -0.5f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.dx = 0.5f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			player.dy = -0.5f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.dy = 0.5f;
		}
	}

	void Update(double deltaTime) {
		pollInput(deltaTime);
		for (int i = 0; i < otherEntity.size(); i++) {
			if (player.overlaps(otherEntity[i])) {
				otherEntity[i].sprite.setFillColor(sf::Color::Red);
				player.dx = -player.dx;
				player.dy = -player.dy;
			}
		}
		player.UpdateEntity();
	}
	void cacheWall() {
		wallsRender.clear();
		for (sf::Vector2i& w : walls) {
			sf::RectangleShape rect(sf::Vector2f(16, 16));
			rect.setPosition(w.x * Entity::GRID_SIZE, w.y * Entity::GRID_SIZE);
			rect.setFillColor(sf::Color::Green);
			wallsRender.push_back(rect);
		}
	}
	void draw() {
		win->draw(player.sprite);
		for (int i = 0; i < otherEntity.size(); i++) {
			win->draw(otherEntity[i].sprite);
		}
		for (sf::RectangleShape& w : wallsRender) {
			win->draw(w);
		}
	}
};
