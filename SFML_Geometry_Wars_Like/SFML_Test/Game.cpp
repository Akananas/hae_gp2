#include "Game.hpp"
#include "HotReloadShader.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"

Game::Game(sf::RenderWindow* win) {
	this->win = win;
	curView = win->getView();
	if (!cursor.loadFromFile("../res/crossair_white.png")) {
		std::cout << "ERROR NO FONT" << std::endl;
	}
	if (!gameFont.loadFromFile("../res/Squares Bold Free.otf")) {
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
	chargeAttack = new HotReloadShader("../res/player.vert", "../res/player.frag");
	shockwave = new HotReloadShader("../res/simple.vert", "../res/displace.frag");
	winTex.create(win->getSize().x, win->getSize().y);
	noise.loadFromFile("../res/noise.png");
	curSave = ReadSaveFile();
	money = curSave.savedMoney;
	highScore = curSave.Highscore;
	maxLevel = curSave.MaxLevel;

	moneyText.setFont(gameFont);
	moneyText.setCharacterSize(24);
	moneyText.setPosition(1200, 20);
	moneyText.setFillColor(sf::Color::White);

	scoreText.setFont(gameFont);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(sf::Vector2f(640 , 20));
	scoreText.setFillColor(sf::Color::White);

	levelText.setFont(gameFont);
	levelText.setCharacterSize(24);
	levelText.setString("Level: " + to_string(level));
	levelText.setPosition(sf::Vector2f(340, 20));

	fpsText.setFont(gameFont);
	fpsText.setCharacterSize(24);
	fpsText.setPosition(sf::Vector2f(60, 20));

	cursorPos.setSize(sf::Vector2f(32, 32));
	cursorPos.setOrigin(sf::Vector2f(16, 16));
	cursorPos.setTexture(&cursor);

	player = Player(this);
	player.LoadSave(curSave.savedDamageLevel, curSave.savedAttackSpeedLevel, curSave.savedBomb);

	bombText.setFont(gameFont);
	bombText.setCharacterSize(24);
	bombText.setPosition(sf::Vector2f(640, 50));
	bombText.setFillColor(sf::Color::White);
	UpdateBombText();

	StartMenu();
	for (int i = 0; i < cols; ++i) {
		walls.push_back(sf::Vector2i(i, lastLine - 1));
		walls.push_back(sf::Vector2i(i, 0));
	}
	for (int i = 0; i < lastLine - 1; ++i) {
		walls.push_back(sf::Vector2i(0, i));
		walls.push_back(sf::Vector2i(cols - 1, i));
	}
	cacheWall();
}
static float g_time = 0.0;

void Game::processInput(sf::Event event) {
	curScene->ProcessInput(event);
}

void Game::pollInput(double dt) {
	bool keyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) ||
					  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
					  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) ||
					  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		player.dx = -0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		player.dx = 0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		player.dy = -0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		player.dy = 0.5f;
	}
	if (keyPressed) {
		particleManager.push_back(ParticleSystem(8, sf::Color(86, 61, 245), player.GetPosition(), false, 50, 0.5));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && player.isAlive && shootCooldown >= player.attackSpeed &&
		(dynamic_cast<GameScene*>(curScene)
		|| dynamic_cast<MenuScene*>(curScene) && bullet.size() == 0)){
		Shoot();
	}
}

void Game::Update(double deltaTime) {
	g_time += deltaTime;
	if (shootTimer < 1.5f) {
		shootTimer += deltaTime;
	}
	if (chargeAttack) chargeAttack->update(deltaTime);
	if (shockwave) shockwave->update(deltaTime);
	if (respawnTimer > 10) {
		respawn = false;
	}
	else if (respawn) {
		respawnTimer += deltaTime;
	}
	if (shootCooldown < player.attackSpeed) {
		shootCooldown += deltaTime;
	}
	if (player.isAlive) {
		pollInput(deltaTime);
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
	curScene->UpdateScene(deltaTime);
	for (int i = floatingText.size() - 1; i >= 0; i--) {
		floatingText[i].UpdateText(deltaTime);
		if (floatingText[i].destroyed) {
			floatingText.erase(floatingText.begin() + i);
		}
	}
	for (int i = bullet.size() - 1; i >= 0; i--) {
		if (bullet[i].destroyed) {
			sf::Vector2f bulPos = sf::Vector2f(bullet[i].GetPositionCase() * Entity::GRID_SIZE);
			particleManager.push_back(ParticleSystem(200, bullet[i].explosionColor, bulPos, false, 250, 1.5f));
			bullet.erase(bullet.begin() + i);
		}
	}
	scoreText.setString("SCORE: " + to_string(score));
	moneyText.setString(to_string(money));
	sf::FloatRect textBounds = moneyText.getLocalBounds();
	moneyText.setPosition(sf::Vector2f(1200 - textBounds.width / 2.0, 20));
	fpsText.setString("FPS: " + std::to_string((int)(1 / deltaTime)));
	cursorPos.setPosition(sf::Vector2f(sf::Mouse::getPosition(*win)));

}
void Game::cacheWall() {
	wallsRender.clear();
	for (sf::Vector2i& w : walls) {
		CreateWall(w);
	}
}
void Game::CreateWall(sf::Vector2i& w) {
	sf::RectangleShape rect(sf::Vector2f(16, 16));
	rect.setPosition(w.x * Entity::GRID_SIZE, w.y * Entity::GRID_SIZE);
	rect.setFillColor(sf::Color(1, 141, 104));
	wallsRender.push_back(rect);
}
bool Game::isWall(float cx, float cy) {
	for (sf::Vector2i& w : walls) {
		if (cx == w.x && cy == w.y) {
			return true;
		}
	}
	return false;
}

void Game::StartMenu() {
	delete curScene;
	curScene = nullptr;
	MenuScene* menu = new MenuScene(this);
	curScene = menu;
	curScene->InitScene();
	player.KillPlayer();
}
void Game::StartGame() {
	delete curScene;
	curScene = nullptr;
	GameScene* gScene = new GameScene(this);
	curScene = gScene;
	curScene->InitScene();
	player.KillPlayer();
	score = 0;
	level = 0;
	UpgradeLevel();
}

void Game::SwitchMenu(MenuObject& val, int& index) {
	switch (val.ReturnVal()) {
	case StartState:
		StartGame();
		break;
	case PowerUpState:
		if (money - (5 * player.damageLevel) >= 0) {
			player.damage += 1;
			money -= (5 * player.damageLevel);
			player.damageLevel++;
			val.SetPrice(5 * player.damageLevel);
			FloatingText text("Damage Up", gameFont, player.GetPosition(), val.GetColor());
			floatingText.push_back(text);
			powerUpSound.play();
		}
		break;
	case AttackSpeedState:
		if (money - (5 * player.attackSpeedLevel) >= 0) {
			player.UpAttackSpeed();
			money -= (5 * player.attackSpeedLevel);
			player.attackSpeedLevel++;
			val.SetPrice(5 * player.attackSpeedLevel);
			FloatingText text("Attack Speed Up",gameFont,player.GetPosition(), val.GetColor());
			floatingText.push_back(text);
			powerUpSound.play();
		}
		break;
	case BombState:
		if (money - 50 >= 0 && player.bomb < 5) {
			player.bomb++;
			money -= 50;
			FloatingText text("+1 Bomb", gameFont, player.GetPosition(), val.GetColor());
			floatingText.push_back(text);
			powerUpSound.play();
			UpdateBombText();
		}
		break;
	default:
		break;
	}
}
void Game::UpdateBombText() {
	bombText.setString("Bomb: " + to_string(player.bomb));
}
void Game::AddMoney(int _money) {
	money += _money;
}
void Game::UpgradeLevel() {
	level++;
	levelText.setString("Level: " + std::to_string(level));
}

void Game::PlayerView() {
	curView.setCenter(player.GetPosition());
	win->setView(curView);
}
void Game::drawGame() {
	win->draw(stars);
	{
		sf::RenderStates states = sf::RenderStates::Default;
		sf::Shader* sh = &chargeAttack->sh;
		states.shader = sh;
		sh->setUniform("texture", sf::Shader::CurrentTexture);
		sh->setUniform("time", shootTimer);
		sh->setUniform("maxTime", 1.5f);
		win->draw(player,states);
	}
	win->draw(*curScene);
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
	if (respawn) {
		{
			winTex.update(*win);
			sf::Sprite sp(winTex);
			sf::RenderStates states = sf::RenderStates::Default;
			sf::Shader* sh = &shockwave->sh;
			states.shader = sh;
			sh->setUniform("texture", winTex);
			sh->setUniform("noise", noise);
			sh->setUniform("time", respawnTimer);
			sh->setUniform("maxTime", 0.5f);
			sh->setUniform("center", sf::Vector2f(0.5f, 0.5f));
			win->setView(win->getDefaultView());
			win->draw(sp, states);
		}
	}
}

void Game::drawUI() {
	win->draw(moneyText);
	win->draw(scoreText);
	win->draw(levelText);
	win->draw(fpsText);
	win->draw(bombText);
	win->draw(cursorPos);
}

void Game::Shoot() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
	sf::Vector2f mouseWorld = win->mapPixelToCoords(mousePos);
	sf::Vector2f dir = mouseWorld - player.GetPosition();
	sf::Vector2f normalized(dir.x / sqrt(dir.x * dir.x + dir.y * dir.y), dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
	if (dynamic_cast<MenuScene*>(curScene)) {
		bullet.push_back(Bullet(this, player.GetPosition(), normalized, player.damageLevel * (1 + shootTimer / 1.5f)));
	}
	else {
		for (int i = -player.bulletNum / 2; i < (player.bulletNum + 1) / 2; i++) {
			sf::Vector2f spawnPos(player.GetPosition() + sf::Vector2f(16 * normalized.y * i, 16 * normalized.x * -i));
			bullet.push_back(Bullet(this, spawnPos, normalized, player.damageLevel * 2 * shootTimer / 1.5f));
			if (spawnPos.x > cols * Entity::GRID_SIZE || spawnPos.y > lastLine * Entity::GRID_SIZE || spawnPos.x < 0 || spawnPos.y < 0) {
				bullet[bullet.size() - 1].destroyed = true;
			}
		}
	}
	shootCooldown = 0;
	shootTimer = 0;
	attackSound.play();
}

void Game::CheckHighscore() {
	if (score > highScore) {
		highScore = score;
	}
	if (level > maxLevel) {
		maxLevel = level;
	}
}
