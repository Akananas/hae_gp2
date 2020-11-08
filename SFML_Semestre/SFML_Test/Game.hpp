#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Lib.hpp"
class Game {
public:
	sf::RenderWindow* win;
	sf::CircleShape player;
	sf::RectangleShape block;

	Game(sf::RenderWindow* win){
		//Get RenderWindow
		this->win = win;
		player.setRadius(10);
		player.setOrigin(5, 5);
		player.setFillColor(sf::Color::Green);
		player.setPosition(300, 300);
		block.setOrigin(5, 5);
		block.setSize(sf::Vector2f(10,10));
		block.setPosition(200, 200);

	}

	void processInput(sf::Event event) {
		if (event.type == sf::Event::MouseMoved) {
		}
		if (event.type == sf::Event::MouseButtonPressed) {
		}
	}

	void pollInput(double dt) {
		sf::Vector2f dir(0,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			dir.y--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			dir.y++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			dir.x--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			dir.x++;
		}
		if (dir.x != 0 || dir.y != 0) {
			dir = sf::Vector2f(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
			player.setPosition(player.getPosition() + dir);
		}
	}

	void Update(double deltaTime) {
		pollInput(deltaTime);
		if (player.getGlobalBounds().intersects(block.getGlobalBounds())) {
			block.setFillColor(sf::Color::Red);
		}
	}

	void draw() {
		win->draw(player);
		win->draw(block);
	}
};