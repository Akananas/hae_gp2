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
			sf::Vector2i cell(i, j);
			if (!isWall(i,j)) {
				notWalls.push_back(cell);
			}
		}
	}
	pathfinding = new Pathfinding();
	sf::Vector2i playerPos(player.cx, player.cy);
	pathfinding->UpdatePath(notWalls,  playerPos, this);
	path.setPrimitiveType(sf::LinesStrip);
}
void Game::processInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::LControl) {
			player.Walk();
		}
		if (event.key.code == sf::Keyboard::LShift) {
			player.Run();
		}
		if (event.key.code == sf::Keyboard::A) {
			sf::Vector2i playerPos(player.cx, player.cy);

			pathfinding->UpdatePath(notWalls, playerPos, this);
			path.clear();
		}
	}
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
		mousePos.x /= Entity::GRID_SIZE;
		mousePos.y /= Entity::GRID_SIZE;
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
			if (!isWall(mousePos.x, mousePos.y)) {
				path.clear();
				sf::Vector2i curPos = mousePos;
				while (curPos != pathfinding->start) {
					sf::Vector2f screenPos = sf::Vector2f(curPos * Entity::GRID_SIZE);
					screenPos.x += 8;
					screenPos.y += 8;
					path.append(sf::Vertex(screenPos));
					curPos = pathfinding->parentNode[curPos];
				}
			}
		}
		if (event.mouseButton.button == sf::Mouse::Button::Right) {
			player.MoveTo(mousePos);
		}
	}
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
