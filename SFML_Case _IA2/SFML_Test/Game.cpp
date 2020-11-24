#include "Game.hpp"
#include "HotReloadShader.hpp"
Game::Game(sf::RenderWindow* win) {
	this->win = win;
	bg = sf::RectangleShape(sf::Vector2f(win->getSize().x, win->getSize().y));
	bool isOk = tex.loadFromFile("../res/bg.jpg");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));

	bgShader = new HotReloadShader("../res/bg.vert", "../res/bg_time.frag");
	player = Entity(this);
	player.SetPosition(200, 700);
	/*Entity block(this);
	block.SetPosition(1220, 700);
	otherEntity.push_back(block);*/
	int cols = 1280 / Entity::GRID_SIZE;
	int lastLine = 720 / Entity::GRID_SIZE - 1;
	for (int i = 0; i < cols; ++i) {
		walls.push_back(sf::Vector2i(i, lastLine));
	}
	for (int i = 0; i < cols/2; ++i) {
		walls.push_back(sf::Vector2i(i, lastLine/2));
	}
	for (int i = 0; i < lastLine; ++i) {
		walls.push_back(sf::Vector2i(0, i));
		walls.push_back(sf::Vector2i(cols - 1, i));
	}
	cacheWall();
	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < lastLine; ++j) {
			if (!isWall(i,j)) {
				notWalls.push_back(sf::Vector2i(i, j));
			}
		}
	}
	path.setPrimitiveType(sf::LinesStrip);
}
static float g_time = 0.0;

void Game::Update(double deltaTime) {
	g_time += deltaTime;
	if (bgShader) bgShader->update(deltaTime);
	pollInput(deltaTime);
	/*for (int i = 0; i < otherEntity.size(); i++) {
		player.overlaps(otherEntity[i]);
	}*/
	player.UpdateEntity(deltaTime);
	for (int i = 0; i < particleManager.size(); i ++) {
		particleManager[i].Update(deltaTime);
		if (particleManager[i].destroyed) {
			particleManager.erase(particleManager.begin() + i);
		}
	}
}
void Game::draw() {

	/*sf::RenderStates states = sf::RenderStates::Default;
	sf::Shader* sh = &bgShader->sh;
	///states.texture = bg.getTexture();
	states.blendMode = sf::BlendAdd;
	states.shader = sh;
	sh->setUniform("texture", tex);
	sh->setUniform("time", g_time);
	win->draw(bg, states);*/
	win->draw(bg);
	win->draw(player.sprite);
	for (int i = 0; i < otherEntity.size(); i++) {
		win->draw(otherEntity[i].sprite);
	}
	for (sf::RectangleShape& w : wallsRender) {
		win->draw(w);
	}
	for (Particle& parts : particleManager) {
		win->draw(parts);
	}
	win->draw(path);
}
