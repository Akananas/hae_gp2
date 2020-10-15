#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Tank.hpp"
class Game {
public:
	sf::RenderWindow* win;
	sf::Texture tankText;
	sf::Texture bulletText;
	Tank playerTank;
	sf::RectangleShape player;
	Game(sf::RenderWindow* win){
		tankText.loadFromFile("../res/tank.png");
		//bulletText.loadFromFile("../res/bullet.png");
		playerTank.SetTank(tankText);
		player = sf::RectangleShape(sf::Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setOutlineColor(sf::Color(0x59EB5Dff));
		player.setOrigin(50, 50);
		player.setOrigin(25, 25);
	}
	void processInput(sf::Event event) {
		if (event.type == sf::Event::MouseMoved) {
			//sf::Vector2f dir(sf::Mouse::getPosition(*win).x - playerTank.sprite.getPosition().x, sf::Mouse::getPosition(*win).y - playerTank.sprite.getPosition().y);
			//playerTank.RotateTank(atan(dir.y / dir.x) * 180 / 3.14);
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			Bullet newBullet(playerTank);
		}
	}
	void pollInput() {
		sf::Vector2f pos = player.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			pos.y--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			pos.y++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			pos.x--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			pos.x++;
		}
		player.setPosition(pos);
	}
	void Update() {
		pollInput();
	}

	void draw() {
		win->draw(player);
		//win->draw(playerTank.sprite);
	}
};