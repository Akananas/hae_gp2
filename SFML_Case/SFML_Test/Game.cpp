#include "Game.hpp"

void Game::Update(double deltaTime) {
	g_time += deltaTime;
	if (bgShader) bgShader->update(deltaTime);
	pollInput(deltaTime);
	for (int i = 0; i < otherEntity.size(); i++) {
		player.overlaps(otherEntity[i]);
	}
	player.UpdateEntity(deltaTime);
	for (Particle& parts : particleManager) {
		parts.Update(deltaTime);
	}
}
