#include "Game.hpp"
#include "HotReloadShader.hpp"

Game::Game(sf::RenderWindow* win) {
	this->win = win;
	curView = win->getView();
	if (!moneyFont.loadFromFile("../res/Squares Bold Free.otf")) {
		std::cout << "ERROR NO FONT" << std::endl;
	}
	if (hitSoundBuffer.loadFromFile("../res/Hit_Hurt7.wav")) {
		hitSound.setBuffer(hitSoundBuffer);
		hitSound.setVolume(15);
	}
	if (powerUpSoundBuffer.loadFromFile("../res/Powerup22.wav")) {
		powerUpSound.setBuffer(powerUpSoundBuffer);
		powerUpSound.setVolume(15);
	}
	if (attackSoundBuffer.loadFromFile("../res/Laser_Shoot36.wav")) {
		attackSound.setBuffer(attackSoundBuffer);
		attackSound.setVolume(5);
	}
	if (explosionSoundBuffer.loadFromFile("../res/Explosion57.wav")) {
		explosionSound.setBuffer(explosionSoundBuffer);
		explosionSound.setVolume(15);
	}
	if (bombSoundBuffer.loadFromFile("../res/Explosion80.wav")) {
		bombSound.setBuffer(bombSoundBuffer);
		bombSound.setVolume(15);
	}
	moneyText.setFont(moneyFont);
	moneyText.setCharacterSize(24);
	moneyText.setPosition(1200, 20);
	moneyText.setFillColor(sf::Color::White);
	scoreText.setFont(moneyFont);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(sf::Vector2f(640 , 20));
	scoreText.setFillColor(sf::Color::White);

	levelText.setFont(moneyFont);
	levelText.setCharacterSize(24);
	levelText.setString("Level: " + to_string(level));
	levelText.setPosition(sf::Vector2f(340, 20));

	fpsText.setFont(moneyFont);
	fpsText.setCharacterSize(24);
	fpsText.setPosition(sf::Vector2f(60, 20));
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

void Game::processInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			StartGame();
		}
		if (event.key.code == sf::Keyboard::E) {
			if (player.BombAvailable() && playing) {
				particleManager.push_back(ParticleSystem(1000, sf::Color(247, 249, 118), player.GetPosition(), false, 500, 1.5));
				bombSound.play();
				float bombRa = player.bombRadius;
				int bombChain = 0;
				for (int i = fastEnnemy.size() - 1; i >= 0; i--) {
					sf::Vector2f dis = fastEnnemy[i].GetPosition() - player.GetPosition();
					float mag = Entity::getMag(dis);
					if (mag <= bombRa) {
						particleManager.push_back(ParticleSystem(400, sf::Color(118, 5, 72), fastEnnemy[i].GetPosition(), false, 350, 2.5f));
						fastEnnemy.erase(fastEnnemy.begin() + i);
						money += 5 + bombChain;
						score += 50 * (bombChain + 1);
						bombChain++;
					}
				}
				for (int i = slowEnnemy.size() - 1; i >= 0; i--) {
					sf::Vector2f dis = slowEnnemy[i].GetPosition() - player.GetPosition();
					float mag = Entity::getMag(dis);
					if (mag <= bombRa) {
						particleManager.push_back(ParticleSystem(400, sf::Color(118, 5, 72), slowEnnemy[i].GetPosition(), false, 350, 2.5f));
						slowEnnemy.erase(slowEnnemy.begin() + i);
						money += 5 + bombChain;
						score += 50 * (bombChain + 1);
						bombChain++;
					}
				}
				if (bombChain > 1) {
					FloatingText bombText("Bomb Chain: " + std::to_string(bombChain), moneyFont, player.GetPosition(), sf::Color(255, 166, 158));
					floatingText.push_back(bombText);
				}
				player.bomb--;
			}
		}
	}
}

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
		attackSound.play();
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
			if (levelTimer > 10) {
				levelTimer = 0;
				level++;
				levelText.setString("Level: " + to_string(level));
			}
			if (nextSpawnTimer >= 0.5 / (float)level) {
				sf::Vector2f playerPos = player.GetPosition();
				sf::Vector2f spawnPos(20 + (rand() % 1220), 20 + (rand() % 660));
				sf::Vector2f newPos(playerPos - spawnPos);
				while (Entity::getMag(newPos) < 250) {
					spawnPos = sf::Vector2f(20 + (rand() % 1220), 20 + (rand() % 660));
					newPos = playerPos - spawnPos;
				}
				int spawnRate = rand() % 100;
				if (spawnRate < 50) {
					slowEnnemy.push_back(SlowEnnemy(this, level, spawnPos, sf::Color(134, 91, 111)));
				}
				else {
					fastEnnemy.push_back(FastEnnemy(this, level, spawnPos, sf::Color(59, 148, 204)));
				}
				nextSpawnTimer = 0;
			}
			sf::Vector2i playerPosCase = player.GetPositionCase();
			for (int i = fastEnnemy.size() - 1; i >= 0; i--) {
				fastEnnemy[i].UpdateEntity(deltaTime, playerPosCase);
				if (player.overlaps(fastEnnemy[i]) && fastEnnemy[i].canHurtPlayer()) {
					player.KillPlayer();
					for (int j = 0; j < menuObject.size(); j++) {
						menuObject[j].StartSpawn();
					}
					StartMenu();
					fastEnnemy.clear();
					bullet.clear();
					particleManager.push_back(ParticleSystem(4000, sf::Color::Cyan, player.GetPosition(), false, 250, 5));
					break;
				}
			}
			for (int i = slowEnnemy.size() - 1; i >= 0; i--) {
				slowEnnemy[i].UpdateEntity(deltaTime, playerPosCase);
				if (player.overlaps(slowEnnemy[i]) && slowEnnemy[i].canHurtPlayer()) {
					player.KillPlayer();
					for (int j = 0; j < menuObject.size(); j++) {
						menuObject[j].StartSpawn();
					}
					StartMenu();
					fastEnnemy.clear();
					bullet.clear();
					particleManager.push_back(ParticleSystem(4000, sf::Color::Cyan, player.GetPosition(), false, 250, 5));
					break;
				}
			}
			nextSpawnTimer += deltaTime;
			levelTimer += deltaTime;
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
	stars.UpdateStars(deltaTime, player.GetSpeed());
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
			for (int j = 0; j < fastEnnemy.size(); j++) {
				if (bullet[i].overlaps(fastEnnemy[j])) {
					bullet[i].destroyed = true;
					explosionColor = fastEnnemy[j].sprite.getFillColor();
					if (fastEnnemy[j].getDamage(player.damage)) {
						fastEnnemy.erase(fastEnnemy.begin() + j);
						money += 5 * level;
						score += 100 * level;
						explosionSound.play();
					}
					else {
						hitSound.play();
					}
				}
			}
			for (int j = 0; j < slowEnnemy.size(); j++) {
				if (bullet[i].overlaps(slowEnnemy[j])) {
					bullet[i].destroyed = true;
					explosionColor = slowEnnemy[j].sprite.getFillColor();
					if (slowEnnemy[j].getDamage(player.damage)) {
						slowEnnemy.erase(slowEnnemy.begin() + j);
						money += 5 * level;
						score += 100 * level;
						explosionSound.play();
					}
					else {
						hitSound.play();
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
	fpsText.setString("FPS: " + std::to_string((int)(1 / deltaTime)));
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
			powerUpSound.play();
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
			powerUpSound.play();

		}
	case BombState:
		if (money - 50 >= 0 && player.bomb < 5) {
			player.bomb++;
			money -= 50;
			FloatingText text("+1 Bomb", moneyFont, player.GetPosition(), menuObject[index].GetColor());
			floatingText.push_back(text);
			powerUpSound.play();

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
void Game::drawUI() {
	win->draw(moneyText);
	win->draw(scoreText);
	win->draw(levelText);
	win->draw(fpsText);
}
void Game::drawGame() {
	win->draw(stars);
	win->draw(player);
	if (playing) {
		for (int i = 0; i < fastEnnemy.size(); i++) {
			win->draw(fastEnnemy[i]);
		}
		for (int i = 0; i < slowEnnemy.size(); i++) {
			win->draw(slowEnnemy[i]);
		}
	}
	else {
		for (int i = 0; i < menuObject.size(); i++) {
			win->draw(menuObject[i]);
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
