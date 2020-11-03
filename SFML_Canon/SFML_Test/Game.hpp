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
	sf::Vector2f defaultSize;

	//Viseur
	sf::Vertex mouseScope[3] = {};

	//Sprite
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::RectangleShape player;
	sf::RectangleShape cannon;

	//Sound
	sf::Sound laser;
	sf::SoundBuffer laserBuffer;
	sf::Sound bulletExplosion;
	sf::SoundBuffer bulletExplosionBuffer;
	sf::Texture spaceship;
	sf::Music music;

	sf::Vector2f lastValidDir;

	float playerSpeed = 7.5;
	bool firing = false;
	bool augmentSize = false;
	std::vector<Bullet> bullets;

	bool canScreenShake = false;
	int screenShakeTimer = 0;


	std::vector<Particles> particles;

	float getMag(sf::Vector2f vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	Game(sf::RenderWindow* win){
		//Get RenderWindow
		this->win = win;
		defaultSize = win->getView().getSize();

		//Create player
		player = sf::RectangleShape(sf::Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setFillColor(sf::Color::Red);
		player.setOrigin(32, 32);
		player.setPosition(win->getSize().x / 2.0, win->getSize().y/ 2.0);

		//Create cannon
		cannon = sf::RectangleShape(sf::Vector2f(50, 10));
		cannon.setFillColor(sf::Color::White);
		cannon.setOrigin(0,5);
		cannon.setPosition(player.getPosition());

		//Create background
		background.loadFromFile("../res/bg5.jpg");
		backgroundSprite.setTexture(background);
		backgroundSprite.setColor(sf::Color(255, 255, 255, 255));

		//Load shooting sound
		laserBuffer.loadFromFile("../res/laser1.ogg");
		laser.setBuffer(laserBuffer);
		laser.setVolume(10);

		//Load bullet sound
		bulletExplosionBuffer.loadFromFile("../res/laser4.ogg");
		bulletExplosion.setBuffer(bulletExplosionBuffer);
		bulletExplosion.setVolume(10); 
		
		//Load music
		music.openFromFile("../res/music.ogg");
		music.setVolume(10);
		music.setLoop(true);
		music.play();

		for (int i = 0; i < 3; i++) {
			mouseScope[i].color = sf::Color::Green;
		}
	}

	void FiringEffect() {
		sf::Vector2f sizeCannon = cannon.getSize();

		//Shrink cannon
		if (!augmentSize) {
			if (sizeCannon.x > 25) {
				sizeCannon.x -= 5;
			}
			else {
				augmentSize = true;
			}
		}

		//Expand cannon
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
				Particles tmp(bulletPos, dir,0.25, 2, sf::Vector2f(5,5), sf::Color::Yellow, 1, 1);
				particles.push_back(tmp);
			}
			for (int i = 0; i < 10; i++) {
				Particles tmp(bulletPos, dir, 0.25, 3.5, sf::Vector2f(7.5, 7.5), sf::Color::Red, 1, 1);
				particles.push_back(tmp);
			}
			for (int i = 0; i < 5; i++) {
				Particles tmp(bulletPos, dir, 0.25, 2.75, sf::Vector2f(6, 6), sf::Color(255, 111, 0), 1, 1);
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
			Particles part(pos - (dir * (float)2), -dir, 1.5, 0.25, sf::Vector2f(10, 10), sf::Color(125,125,125), 5, 0);
			particles.push_back(part);
			Particles roue1(pos - (dir * (float)2), sf::Vector2f(0, 0), 1.5, 0.25, sf::Vector2f(10, 10), sf::Color::Red, 1, 0);
			Particles roue2(pos - (dir * (float)2), sf::Vector2f(0,0), 1.5, 0.25, sf::Vector2f(10, 10), sf::Color::Red, 1, 0);
			particles.push_back(roue1);
			particles.push_back(roue2);
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