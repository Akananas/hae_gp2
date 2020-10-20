#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Particles.hpp"
#include "Lib.hpp"
class Game {
public:
	sf::RenderWindow* win;
	sf::RectangleShape player;
	sf::RectangleShape cannon;
	std::vector<Bullet> bullets;
	sf::Vertex mouseScope[3] = {};
	sf::Vector2f defaultSize;
	sf::Vector2f lastValidDir;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::Sound laser;
	sf::SoundBuffer laserBuffer;
	sf::Sound bulletExplosion;
	sf::SoundBuffer bulletExplosionBuffer;
	sf::Texture spaceship;
	bool firing = false;
	bool augmentSize = false;
	bool canScreenShake = false;
	int screenShakeTimer = 0;
	float playerSpeed = 7.5;
	std::vector<Particles> particles;

	float getMag(sf::Vector2f vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	Game(sf::RenderWindow* win){
		this->win = win;
		player = sf::RectangleShape(sf::Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setFillColor(sf::Color::Red);
		player.setOrigin(32, 32);
		player.setPosition(win->getSize().x / 2.0, win->getSize().y/ 2.0);
		cannon = sf::RectangleShape(sf::Vector2f(50, 10));
		cannon.setFillColor(sf::Color::White);
		cannon.setOrigin(0,5);
		cannon.setPosition(player.getPosition());
		defaultSize = win->getView().getSize();
		background.loadFromFile("../res/bg5.jpg");
		backgroundSprite.setTexture(background);
		backgroundSprite.setColor(sf::Color(255, 255, 255, 255));
		laserBuffer.loadFromFile("../res/laser1.ogg");
		laser.setBuffer(laserBuffer);
		laser.setVolume(10);
		bulletExplosionBuffer.loadFromFile("../res/laser4.ogg");
		bulletExplosion.setBuffer(bulletExplosionBuffer);
		bulletExplosion.setVolume(10);
		for (int i = 0; i < 3; i++) {
			mouseScope[i].color = sf::Color::Green;
		}
	}

	void FiringEffect() {
		sf::Vector2f sizeCannon = cannon.getSize();
		if (!augmentSize) {
			if (sizeCannon.x > 25) {
				sizeCannon.x -= 5;
			}
			else {
				augmentSize = true;
			}
		}
		if (augmentSize) {
			if (sizeCannon.x <= 25) {
				sizeCannon.x += 5;
			}
			else {
				sizeCannon.x = 50;
				firing = false;
				augmentSize = false;
			}
		}
		cannon.setSize(sizeCannon);
		cannon.setOrigin(0 , 5);
	}

	void screenShake() {
		sf::View screenView = win->getView();
		screenView.move(rand() % 15, rand() % 10);
		win->setView(screenView);
		screenShakeTimer++;
	}
	void UpdateCannon() {
		sf::Vector2f dir(sf::Mouse::getPosition(*win).x - player.getPosition().x, sf::Mouse::getPosition(*win).y - player.getPosition().y);
		cannon.setRotation(atan2(dir.y, dir.x) * 180 / 3.14);
	}
	void processInput(sf::Event event) {
		if (event.type == sf::Event::MouseMoved) {
			UpdateCannon();
			mouseScope[1].position = (sf::Vector2f)sf::Mouse::getPosition(*win);
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f dir(sf::Mouse::getPosition(*win).x - player.getPosition().x, sf::Mouse::getPosition(*win).y - player.getPosition().y);
			Bullet _bullet(player.getPosition(), dir);
			bullets.push_back(_bullet);
			firing = true;
			laser.play();
			sf::Vector2f bulletPos = _bullet.circle.getPosition();
			for (int i = 0; i < 30; i++) {
				Particles tmp(bulletPos, dir,0.25, 2, sf::Vector2f(5,5), sf::Color(125,125,125));
				particles.push_back(tmp);
			}
		}
	}

	void pollInput(double dt) {
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
			dir = sf::Vector2f(dir.x / magDir, dir.y / magDir) * (float)60.0 * playerSpeed * (float)dt;
			Particles part(pos, dir, 1.5, 0.25, sf::Vector2f(10, 10), sf::Color::Blue);
			particles.push_back(part);
		}
		player.setPosition(pos + dir);
		cannon.setPosition(pos + dir);
		mouseScope[0].position = player.getPosition();
		UpdateCannon();
	}

	void BulletUpdate(double deltaTime) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].Move(deltaTime);
			if (bullets[i].checkPos()) {
				bullets.erase(bullets.begin() + i);
				bulletExplosion.play();
				screenShakeTimer = 0;
				canScreenShake = true;
			}
		}
	}
	void ParticlesUpdate(double deltaTime) {
		for (int i = 0; i < particles.size(); i++) {
			if (particles[i].Update(deltaTime)) {
				particles.erase(particles.begin() + i);
			}
		}
	}

	void Update(double deltaTime) {
		pollInput(deltaTime);
		BulletUpdate(deltaTime);
		ParticlesUpdate(deltaTime);
		if (firing) {
			FiringEffect();
		}
		if (canScreenShake && screenShakeTimer < 5) {
			screenShake();
		}
		else if(canScreenShake && screenShakeTimer >= 5){
			canScreenShake = false;
			win->setView(win->getDefaultView());
		}
	}

	void draw() {
		win->draw(backgroundSprite);
		win->draw(player);
		win->draw(cannon);
		sf::Vector2f lastVert = (mouseScope[1].position - mouseScope[0].position);
		mouseScope[2].position = getMag((sf::Vector2f)win->getSize() - lastVert) * lastVert;
		win->draw(mouseScope, 3, sf::LinesStrip);
		for (int i = 0; i < bullets.size(); i++) {
			win->draw(bullets[i].circle);
		}
		for (int i = 0; i < particles.size(); i++) {
			win->draw(particles[i].shape);
		}
	}
};