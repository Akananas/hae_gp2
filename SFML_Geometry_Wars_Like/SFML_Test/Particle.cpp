#include "Particle.hpp"

void Particle::MoveY() {
	ry += dy;
	while (ry > 1) {
		ry--;
		cy++;
	}
	while (ry < 0) {
		ry++;
		cy--;
	}
}

void Particle::MoveX() {
	rx += dx;
	while (rx > 1) {
		rx--;
		cx++;
	}
	while (rx < 0) {
		rx++;
		cx--;
	}
}
