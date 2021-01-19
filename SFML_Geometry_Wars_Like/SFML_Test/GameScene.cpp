#include "GameScene.hpp"

void GameScene::InitScene() {
	nextSpawnTimer = 0;
	levelTimer = 0;
}

void GameScene::UpdateScene(double dt) {
	if (levelTimer > 10) {
		levelTimer = 0;
		game->UpgradeLevel();
		if (val->level%5 == 0) {
			//Spawn boss
			for (int i = 0; i < val->level / 5; i++) {
				sf::Vector2f spawnPos(FindSpawn());
				Boss* boss = new Boss(game, val->level, spawnPos);
				enemy.push_back(boss);
			}
		}
	}
	if (nextSpawnTimer >= 0.5f / ((float)val->level * 0.25f)) {
		sf::Vector2f spawnPos(FindSpawn());
		int spawnRate = rand() % 100;
		if (spawnRate < 33) {
			SlowEnemy* en = new SlowEnemy(game, val->level, spawnPos, sf::Color(134, 91, 111));
			enemy.push_back(en);
		}
		else if (spawnRate < 66){
			FastEnemy* en = new FastEnemy(game, val->level, spawnPos, sf::Color(59, 148, 204));
			enemy.push_back(en);
		}
		else {
			RotateEnemy* en = new RotateEnemy(game, val->level, spawnPos, sf::Color(177, 73, 209));
			enemy.push_back(en);
		}
		nextSpawnTimer = 0;
	}
	sf::Vector2i playerPosCase = game->player.GetPositionCase();
	//Update enemies
	for (int i = enemy.size() - 1; i >= 0; i--) {
		enemy[i]->UpdateEntity(dt, playerPosCase);
		//Check collision with player
		if (game->player.overlaps(*enemy[i]) && enemy[i]->canHurtPlayer()) {
			game->player.KillPlayer();
			for (Enemy* en : enemy) {
				delete en;
				en = nullptr;
			}
			enemy.clear();
			game->EndGame();
			return;
		}
	}
	nextSpawnTimer += dt;
	levelTimer += dt;
	//Update bullets
	for (int i = game->bullet.size() - 1; i >= 0; i--) {
		game->bullet[i].UpdateEntity(dt);
		//Check collision
		for (int j = enemy.size() - 1; j >= 0; j--) {
			if (game->bullet[i].overlaps(*enemy[j])) {
				game->bullet[i].destroyed = true;
				game->bullet[i].hitPos = enemy[j]->GetPosition();
				game->bullet[i].explosionColor = enemy[j]->sprite.getFillColor();
				if (enemy[j]->getDamage(game->bullet[i].damage)) {
					delete enemy[j];
					enemy[j] = nullptr;
					enemy.erase(enemy.begin() + j);
					val->money += 5 * val->level;
					val->score += 100 * val->level;
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
		//Return to menu
		if (event.key.code == sf::Keyboard::Space) {
			game->StartMenu();
			return;
		}
		//Use bomb
		if (event.key.code == sf::Keyboard::E) {
			if (game->player.BombAvailable()) {
				game->particleManager.push_back(ParticleSystem(1000, sf::Color(247, 249, 118), game->player.GetPosition(), false, 500, 1.5));
				game->bombSound.play();
				float bombRa = game->player.bombRadius;
				int bombChain = BombDamage(bombRa);
				if (bombChain > 1) {
					FloatingText bombText("Bomb Chain: " + std::to_string(bombChain), game->gameFont, game->player.GetPosition(), sf::Color(255, 166, 158));
					game->floatingText.push_back(bombText);
				}
				game->player.bomb--;
				game->hud.UpdateBombText(&game->player.bomb);
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
			val->money += 5 + bombChain;
			val->score += 50 * (bombChain + 1);
			bombChain++;
		}
	}
	return bombChain;
}

sf::Vector2f GameScene::FindSpawn() {
	sf::Vector2f playerPos = game->player.GetPosition();
	sf::Vector2f spawnPos(20 + (rand() % 1220), 20 + (rand() % 660));
	sf::Vector2f newPos(playerPos - spawnPos);
	while (Entity::getMag(newPos) < 250) {
		spawnPos = sf::Vector2f(20 + (rand() % 1220), 20 + (rand() % 660));
		newPos = playerPos - spawnPos;
	}
	return spawnPos;
}
