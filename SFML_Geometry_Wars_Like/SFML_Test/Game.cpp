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

	player = Player(this);
	player.SetPosition(200, 700);
	e = Ennemy();
	e.SetPosition(400, 200);
	ennemy.push_back(&e);
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

void Game::Update(double deltaTime) {
	g_time += deltaTime;
	if (bgShader) bgShader->update(deltaTime);
	if (shootCooldown < 0.1) {
		shootCooldown += deltaTime;
	}
	pollInput(deltaTime);
	for (int i = 0; i < ennemy.size(); i++) {
		if (player.overlaps(*ennemy[i])) {
			player.Pushback(*ennemy[i]);
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
		bullet[i].UpdateEntity(deltaTime);
		for (int j = 0; j < ennemy.size(); j++) {
			if (bullet[i].overlaps(*ennemy[j])) {
				bullet[i].destroyed = true;
			}
		}
		if (bullet[i].destroyed) {
			sf::Vector2f bulPos = bullet[i].GetPosition();
			particleManager.push_back(ParticleSystem(150,sf::Color::Yellow,bulPos, false,250));
			bullet.erase(bullet.begin() + i);
		}
	}

}
void Game::draw() {
	win->draw(player);
	/*for (int i = 0; i < ennemy.size(); i++) {
		win->draw(*ennemy[i]);
	}*/
	win->draw(e);
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
