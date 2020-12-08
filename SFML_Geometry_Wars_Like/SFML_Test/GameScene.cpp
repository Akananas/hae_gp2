#include "GameScene.hpp"

void GameScene::InitScene() {
	nextSpawnTimer = 0;
	levelTimer = 0;
}

void GameScene::UpdateScene(double dt) {
	if (levelTimer > 10) {
		levelTimer = 0;
		game->UpgradeLevel();
	}
	if (nextSpawnTimer >= 0.5f / ((float)game->level * 0.25f)) {
		sf::Vector2f playerPos = game->player.GetPosition();
		sf::Vector2f spawnPos(20 + (rand() % 1220), 20 + (rand() % 660));
		sf::Vector2f newPos(playerPos - spawnPos);
		while (Entity::getMag(newPos) < 250) {
			spawnPos = sf::Vector2f(20 + (rand() % 1220), 20 + (rand() % 660));
			newPos = playerPos - spawnPos;
		}
		int spawnRate = rand() % 100;
		if (spawnRate < 33) {
			SlowEnemy* en = new SlowEnemy(game, game->level, spawnPos, sf::Color(134, 91, 111));
			enemy.push_back(en);
		}
		else if (spawnRate < 66){
			FastEnemy* en = new FastEnemy(game, game->level, spawnPos, sf::Color(59, 148, 204));
			enemy.push_back(en);
		}
		else {
			RotateEnemy* en = new RotateEnemy(game, game->level, spawnPos, sf::Color(177, 73, 209));
			enemy.push_back(en);
		}
		nextSpawnTimer = 0;
	}
	sf::Vector2i playerPosCase = game->player.GetPositionCase();
	for (int i = enemy.size() - 1; i >= 0; i--) {
		enemy[i]->UpdateEntity(dt, playerPosCase);
		if (game->player.overlaps(*enemy[i]) && enemy[i]->canHurtPlayer()) {
			game->player.KillPlayer();
			for (Enemy* en : enemy) {
				delete en;
				en = nullptr;
			}
			enemy.clear();
			game->bullet.clear();
			game->particleManager.push_back(ParticleSystem(4000, sf::Color::Cyan, game->player.GetPosition(), false, 250, 5));
			game->CheckHighscore();
			game->StartMenu();
			return;
		}
	}
	nextSpawnTimer += dt;
	levelTimer += dt;

	for (int i = game->bullet.size() - 1; i >= 0; i--) {
		game->bullet[i].UpdateEntity(dt);
		for (int j = enemy.size() - 1; j >= 0; j--) {
			if (game->bullet[i].overlaps(*enemy[j])) {
				game->bullet[i].destroyed = true;
				game->bullet[i].explosionColor = enemy[j]->sprite.getFillColor();
				if (enemy[j]->getDamage(game->player.damage)) {
					delete enemy[j];
					enemy[j] = nullptr;
					enemy.erase(enemy.begin() + j);
					game->money += 5 * game->level;
					game->score += 100 * game->level;
					game->explosionSound.play();
				}
				else {
					game->hitSound.play();
				}
			}
		}
	}
}

void GameScene::ProcessInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			game->StartMenu();
			return;
		}
		if (event.key.code == sf::Keyboard::E) {
			if (game->player.BombAvailable()) {
				game->particleManager.push_back(ParticleSystem(1000, sf::Color(247, 249, 118), game->player.GetPosition(), false, 500, 1.5));
				game->bombSound.play();
				float bombRa = game->player.bombRadius;
				int bombChain = BombDamage(bombRa);
				if (bombChain > 1) {
					FloatingText bombText("Bomb Chain: " + std::to_string(bombChain), game->moneyFont, game->player.GetPosition(), sf::Color(255, 166, 158));
					game->floatingText.push_back(bombText);
				}
				game->player.bomb--;
				game->UpdateBombText();
			}
		}
	}
}

int GameScene::BombDamage(float& bombRa) {
	int bombChain = 0;
	for (int i = enemy.size() - 1; i >= 0; i--) {
		sf::Vector2f dis = enemy[i]->GetPosition() - game->player.GetPosition();
		float mag = Entity::getMag(dis);
		if (mag <= bombRa) {
			game->particleManager.push_back(ParticleSystem(400, sf::Color(118, 5, 72), enemy[i]->GetPosition(), false, 350, 2.5f));
			enemy.erase(enemy.begin() + i);
			game->money += 5 + bombChain;
			game->score += 50 * (bombChain + 1);
			bombChain++;
		}
	}
	return bombChain;
}
