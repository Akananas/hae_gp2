#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Lib.hpp"
class Game {
public:
	sf::RenderWindow* win;


	Game(sf::RenderWindow* win){
		//Get RenderWindow
		this->win = win;
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

		}
	}

	void Update(double deltaTime) {
		pollInput(deltaTime);
	}

	void draw() {
	}
};