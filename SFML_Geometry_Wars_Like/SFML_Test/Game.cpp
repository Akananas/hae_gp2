#include "Game.hpp"
#include "HotReloadShader.hpp"

Game::Game(sf::RenderWindow* win) {
	this->win = win;
	curView = win->getView();
	bg = sf::RectangleShape(sf::Vector2f(win->getSize().x, win->getSize().y));
	bool isOk = tex.loadFromFile("../res/bg.jpg");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));
	StartGame();
	int cols = 1280 / Entity::GRID_SIZE;
	int lastLine = 720 / Entity::GRID_SIZE - 1;
	for (int i = 0; i < cols; ++i) {
		walls.push_back(sf::Vector2i(i, lastLine));
		walls.push_back(sf::Vector2i(i, 0));
	}
	for (int i = 0; i < lastLine; ++i) {
		walls.push_back(sf::Vector2i(0, i));
		walls.push_back(sf::Vector2i(cols - 1, i));
	}
	cacheWall();
}
static float g_time = 0.0;

void Game::pollInput(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		player.dx = -0.5f;
		particleManager.push_back(ParticleSystem(8, sf::Color(86, 61, 245), player.GetPosition(), false, 50, 0.5));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		player.dx = 0.5f;
		particleManager.push_back(ParticleSystem(8, sf::Color(86, 61, 245), player.GetPosition(), false, 50, 0.5));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		player.dy = -0.5f;
		particleManager.push_back(ParticleSystem(8, sf::Color(86, 61, 245), player.GetPosition(), false, 50, 0.5));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		player.dy = 0.5f;
		particleManager.push_back(ParticleSystem(8, sf::Color(86, 61, 245), player.GetPosition(), false, 50,0.5));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shootCooldown >= player.attackSpeed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
		sf::Vector2f mouseWorld = win->mapPixelToCoords(mousePos);
		sf::Vector2f dir = mouseWorld - player.GetPosition();
		sf::Vector2f normalized(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
		bullet.push_back(Bullet(this, player.GetPosition(), normalized));
		shootCooldown = 0;
	}
}

void Game::Update(double deltaTime) {
	g_time += deltaTime;
	if (bgShader) bgShader->update(deltaTime);
	if (shootCooldown < player.attackSpeed) {
		shootCooldown += deltaTime;
	}
	if (player.isAlive) {
		pollInput(deltaTime);
		sf::Vector2i playerPos = player.GetPositionCase();
		for (int i = 0; i < ennemy.size(); i++) {
			ennemy[i].UpdateEntity(deltaTime, playerPos);
			if (player.overlaps(ennemy[i])) {
				player.KillPlayer();
				ennemy.clear();
				particleManager.push_back(ParticleSystem(4000, sf::Color::Cyan, player.GetPosition(), false, 150, 5));
				continue;
			}
		}
	}

	player.UpdateEntity(deltaTime);
	for (int i = 0; i < particleManager.size(); i ++) {
		if (particleManager[i].isDestroyed()) {
			particleManager.erase(particleManager.begin() + i);
		}
		else {
			particleManager[i].UpdateParticle(deltaTime);
		}
	}
	for (int i = 0; i < bullet.size(); i++) {
		sf::Color explosionColor(sf::Color::Yellow);
		bullet[i].UpdateEntity(deltaTime);
		for (int j = 0; j < ennemy.size(); j++) {
			if (bullet[i].overlaps(ennemy[j])) {
				bullet[i].destroyed = true;
				explosionColor = ennemy[j].sprite.getFillColor();
				if (ennemy[j].getDamage(player.damage)) {
					ennemy.erase(ennemy.begin() + j);
				}
			}
		}
		if (bullet[i].destroyed) {
			sf::Vector2f bulPos = sf::Vector2f(bullet[i].GetPositionCase() * Entity::GRID_SIZE);
			particleManager.push_back(ParticleSystem(200,explosionColor,bulPos, false,250,1.5f));
			bullet.erase(bullet.begin() + i);
		}
	}

}
void Game::draw() {
	win->draw(player);
	for (int i = 0; i < ennemy.size(); i++) {
		win->draw(ennemy[i]);
	}
	for (sf::RectangleShape& w : wallsRender) {
		win->draw(w);
	}
	for (ParticleSystem& parts : particleManager) {
		win->draw(parts);
	}
	for (Bullet& _bullet : bullet) {
		win->draw(_bullet);
	}
}
