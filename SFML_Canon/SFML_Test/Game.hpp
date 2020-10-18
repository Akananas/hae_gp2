#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
class Game {
public:
	sf::RenderWindow* win;
	sf::RectangleShape player;
	std::vector<Bullet> bullets;
	Game(sf::RenderWindow* win){
		this->win = win;
		player = sf::RectangleShape(sf::Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setOutlineColor(sf::Color(0x59EB5Dff));
		player.setOrigin(32, 32);
	}
	void processInput(sf::Event event) {
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2f dir(sf::Mouse::getPosition(*win).x - player.getPosition().x, sf::Mouse::getPosition(*win).y - player.getPosition().y);
			player.setRotation(atan2(dir.y, dir.x) * 180 / 3.14);
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f dir(sf::Mouse::getPosition(*win).x - player.getPosition().x, sf::Mouse::getPosition(*win).y - player.getPosition().y);
			Bullet _bullet(player.getPosition(), dir);
			bullets.push_back(_bullet);
		}
	}
	void pollInput() {
		sf::Vector2f pos = player.getPosition();
		sf::Vector2f dir(0,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && pos.y > (0 + player.getSize().y / 2.0)) {
			dir.y--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && pos.y < (win->getSize().y - player.getSize().y / 2.0)) {
			dir.y++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && pos.x > (0 + player.getSize().x / 2.0)) {
			dir.x--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && pos.x < (win->getSize().x - player.getSize().x / 2.0)) {
			dir.x++;
		}
		if (dir.x != 0 || dir.y != 0) {
			dir = sf::Vector2f(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
		}
		player.setPosition(pos + dir);
	}
	void BulletUpdate() {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].Move();
			if (bullets[i].checkPos()) {
				bullets.erase(bullets.begin() + i);
			}
		}
	}
	void Update() {
		pollInput();
		BulletUpdate();
	}

	void draw() {
		win->draw(player);
		for (int i = 0; i < bullets.size(); i++) {
			win->draw(bullets[i].circle);
		}
	}
};