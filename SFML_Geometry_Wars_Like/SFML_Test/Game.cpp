#include "Game.hpp"
#include "HotReloadShader.hpp"

Game::Game(sf::RenderWindow* win) {
	this->win = win;
	curView = win->getView();
	if (!moneyFont.loadFromFile("../res/Squares Bold Free.otf")) {
		std::cout << "ERROR NO FONT" << std::endl;
	}
	moneyText.setFont(moneyFont);
	moneyText.setCharacterSize(24);
	moneyText.setPosition(1200, 20);
	moneyText.setFillColor(sf::Color::White);
	scoreText.setFont(moneyFont);
	scoreText.setCharacterSize(24);
	sf::FloatRect textBounds = scoreText.getLocalBounds();
	scoreText.setPosition(sf::Vector2f(640 -textBounds.width / 2.0f, 20));
	scoreText.setFillColor(sf::Color::White);
	bg = sf::RectangleShape(sf::Vector2f(win->getSize().x, win->getSize().y));
	bool isOk = tex.loadFromFile("../res/bg.jpg");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));
	player = Player(this);
	CreateMenu();
	StartMenu();
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shootCooldown >= player.attackSpeed && (playing || !playing && bullet.size() == 0)) {
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
		if (playing) {
			sf::Vector2i playerPos = player.GetPositionCase();
			for (int i = ennemy.size() - 1; i >= 0; i--) {
				ennemy[i].UpdateEntity(deltaTime, playerPos);
				if (player.overlaps(ennemy[i])) {
					player.KillPlayer();
					for (int j = 0; j < menuObject.size(); j++) {
						menuObject[j].StartSpawn();
					}
					StartMenu();
					ennemy.clear();
					bullet.clear();
					particleManager.push_back(ParticleSystem(4000, sf::Color::Cyan, player.GetPosition(), false, 150, 5));
					break;
				}
			}
		}
	}
	if (!playing) {
		for (int i = menuObject.size() - 1; i >= 0; i--){
			menuObject[i].UpdateEntity(deltaTime);
			if (player.overlaps(menuObject[i])) {
				player.Pushback(menuObject[i]);
			}
		}
	}
	player.UpdateEntity(deltaTime);
	for (int i = particleManager.size() - 1; i >= 0; i--) {
		if (particleManager[i].isDestroyed()) {
			particleManager.erase(particleManager.begin() + i);
		}
		else {
			particleManager[i].UpdateParticle(deltaTime);
		}
	}
	for (int i = bullet.size() - 1; i >= 0; i--) {
		sf::Color explosionColor(sf::Color(247, 249, 118));
		bullet[i].UpdateEntity(deltaTime);
		if (playing) {
			for (int j = 0; j < ennemy.size(); j++) {
				if (bullet[i].overlaps(ennemy[j])) {
					bullet[i].destroyed = true;
					explosionColor = ennemy[j].sprite.getFillColor();
					if (ennemy[j].getDamage(player.damage)) {
						ennemy.erase(ennemy.begin() + j);
						money += 5 * level;
						score += 100 * level;
					}
				}
			}
		}
		else {
			for (int j = menuObject.size() - 1; j >= 0; j--) {
				if (bullet[i].overlaps(menuObject[j])) {
					bullet[i].destroyed = true;
					explosionColor = menuObject[j].sprite.getFillColor();
					SwitchMenu(menuObject[j].ReturnVal(), j);
				}
			}
		}
		if (bullet[i].destroyed) {
			sf::Vector2f bulPos = sf::Vector2f(bullet[i].GetPositionCase() * Entity::GRID_SIZE);
			particleManager.push_back(ParticleSystem(200,explosionColor,bulPos, false,250,1.5f));
			bullet.erase(bullet.begin() + i);
		}
	}
	for (int i = floatingText.size() - 1; i >= 0; i--) {
		floatingText[i].UpdateText(deltaTime);
		if (floatingText[i].destroyed) {
			floatingText.erase(floatingText.begin() + i);
		}
	}
	scoreText.setString("SCORE: " + to_string(score));
	moneyText.setString(to_string(money));
}
void Game::drawUI(){
	win->draw(moneyText);
	win->draw(scoreText);
}
bool Game::isWall(float cx, float cy) {
	for (sf::Vector2i& w : walls) {
		if (cx == w.x && cy == w.y) {
			return true;
		}
	}
	return false;
}
void Game::CreateMenu() {
	MenuObject start(StartState, sf::Color(71, 191, 255), sf::Vector2f(100, 120), moneyFont, false);
	MenuObject powerUp(PowerUpState, sf::Color(134, 91, 111), sf::Vector2f(260, 120), moneyFont, true);
	MenuObject attackSpeedUp(AttackSpeedState, sf::Color(143, 57, 133), sf::Vector2f(420, 120), moneyFont, true);
	MenuObject BombBuy(BombState, sf::Color(118, 5, 72), sf::Vector2f(580, 120), moneyFont, true, 50);
	menuObject.push_back(start);
	menuObject.push_back(powerUp);
	menuObject.push_back(attackSpeedUp);
	menuObject.push_back(BombBuy);
}
void Game::SwitchMenu(MenuState val, int& index) {
	switch (val) {
	case StartState:
		StartGame();
		break;
	case PowerUpState:
		if (money - (5 * player.damageLevel) >= 0) {
			player.damage += 1;
			money -= (5 * player.damageLevel);
			player.damageLevel++;
			menuObject[index].SetPrice(5 * player.damageLevel);
			FloatingText text("Damage Up", moneyFont, player.GetPosition(), menuObject[index].GetColor());
			floatingText.push_back(text);
		}
		break;
	case AttackSpeedState:
		if (money - (5 * player.attackSpeedLevel) >= 0) {
			player.attackSpeed -= 0.025 * pow(0.85, player.attackSpeedLevel);
			money -= (5 * player.attackSpeedLevel);
			player.attackSpeedLevel++;
			menuObject[index].SetPrice(5 * player.attackSpeedLevel);
			FloatingText text("Attack Speed Up",moneyFont,player.GetPosition(), menuObject[index].GetColor());
			floatingText.push_back(text);
		}
	case BombState:
		if (money - 50 >= 0 && player.bomb < 5) {
			player.bomb++;
			money -= 50;
			FloatingText text("+1 Bomb", moneyFont, player.GetPosition(), menuObject[index].GetColor());
			floatingText.push_back(text);
		}
	default:
		break;
	}
}
void Game::CreateWall(sf::Vector2i& w) {
	sf::RectangleShape rect(sf::Vector2f(16, 16));
	rect.setPosition(w.x * Entity::GRID_SIZE, w.y * Entity::GRID_SIZE);
	//rect.setFillColor(sf::Color(0, 51, 79));
	rect.setFillColor(sf::Color(1, 141, 104));
	wallsRender.push_back(rect);
}
void Game::drawGame() {
	win->draw(player);
	if (playing) {
		for (int i = 0; i < ennemy.size(); i++) {
			win->draw(ennemy[i]);
		}
	}
	else {
		for (int i = 0; i < menuObject.size(); i++) {
			win->draw(menuObject[i]);
			menuObject[i].DrawText(*win);
		}
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
	for (FloatingText& _text : floatingText) {
		win->draw(_text);
	}

}
