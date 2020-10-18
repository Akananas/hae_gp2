#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
class Game {
public:
	sf::RenderWindow* win;
	sf::RectangleShape player;
	std::vector<Bullet> bullets;
	sf::Vertex mouseScope[3] = {};
	float getMag(sf::Vector2f vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}
	Game(sf::RenderWindow* win){
		this->win = win;
		player = sf::RectangleShape(sf::Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setOutlineColor(sf::Color(0x59EB5Dff));
		player.setOrigin(32, 32);
		for (int i = 0; i < 3; i++) {
			mouseScope[i].color = sf::Color::Green;
		}
	}
	void processInput(sf::Event event) {
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2f dir(sf::Mouse::getPosition(*win).x - player.getPosition().x, sf::Mouse::getPosition(*win).y - player.getPosition().y);
			player.setRotation(atan2(dir.y, dir.x) * 180 / 3.14);
			mouseScope[1].position = (sf::Vector2f)sf::Mouse::getPosition(*win);
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
			float magDir = getMag(dir);
			dir = sf::Vector2f(dir.x / magDir, dir.y / magDir);
		}
		player.setPosition(pos + dir);
		mouseScope[0].position = player.getPosition();
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
		sf::Vector2f lastVert = (mouseScope[1].position - mouseScope[0].position);
		mouseScope[2].position = getMag((sf::Vector2f)win->getSize() - lastVert) * lastVert;
		win->draw(mouseScope, 3, sf::LinesStrip);
		for (int i = 0; i < bullets.size(); i++) {
			win->draw(bullets[i].circle);
		}
	}
};