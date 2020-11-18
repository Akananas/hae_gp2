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
	pollInput(deltaTime);
	for (int i = 0; i < ennemy.size(); i++) {
		player.overlaps(*ennemy[i]);
	}
	player.UpdateEntity(deltaTime);
	for (int i = 0; i < particleManager.size(); i ++) {
		particleManager[i].UpdateEntity(deltaTime);
		if (particleManager[i].destroyed) {
			particleManager.erase(particleManager.begin() + i);
		}
	}
	for (int i = 0; i < bullet.size(); i++) {
		bullet[i].UpdateEntity(deltaTime);
		if (bullet[i].destroyed) {
			sf::Vector2f bulPos = bullet[i].GetPosition();
			for (int j = 0; j < 41; j++) {
				float angle = float(j * (360.0 / 40.0));
				float degree = (angle * 3.14531 /180.0 );
				sf::Vector2f partSpeed(cos(angle) , sin(angle));
				particleManager.push_back(Particle(this, bulPos, -sf::Vector2f(partSpeed.x / 1.25, partSpeed.y / 1.25), sf::Color::Yellow, 0.25));
			}
			bullet.erase(bullet.begin() + i);
		}
	}

}
void Game::draw() {
	win->draw(player);
	for (int i = 0; i < ennemy.size(); i++) {
		win->draw(*ennemy[i]);
	}
	for (sf::RectangleShape& w : wallsRender) {
		win->draw(w);
	}
	for (Particle& parts : particleManager) {
		win->draw(parts);
	}
	for (Bullet& _bullet : bullet) {
		win->draw(_bullet);
	}
}
