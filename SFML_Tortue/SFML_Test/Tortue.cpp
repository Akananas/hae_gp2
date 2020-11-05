
#include "Tortue.hpp"

void Tortue::RotateTortue(float angle, double dt) {
	if (nextRotate == 0) {
		nextRotate = angle;
	}
	float beforeRotate = nextRotate;
	nextRotate -= rotSpeed * angle * dt;
	if (beforeRotate > 0 && nextRotate <= 0 || beforeRotate < 0 && nextRotate >= 0) {
		nextRotate = 0;
		tortue.rotate(beforeRotate);
	}
	else {
		tortue.rotate(rotSpeed * angle * dt);
	}
	direction.setRotation(tortue.getRotation());
}

void Tortue::Move(double dt, int side) {
	if (pixelToMove <= 0) {
		pixelToMove = 20;
 	}
	else {
		pixelToMove -= speed * 20 * dt;
	}
	sf::Vector2f tortuePos = tortue.getPosition();
	sf::Vector2f dir = rotateVector(tortuePos);
	dir.x *= speed * side * 20 * dt;
	dir.y *= speed * side * 20 * dt;
	tortuePos.x += dir.x;
	tortuePos.y += dir.y;
	tortue.setPosition(tortuePos);
	direction.setPosition(tortuePos);
}
