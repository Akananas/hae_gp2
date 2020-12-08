#pragma once
#include "SFML/Graphics.hpp"
class Game;
class Entity : public sf::Drawable{
public:
	static const int GRID_SIZE = 16;
	sf::RectangleShape sprite;
	float radius = 0;
	bool destroyed = false;

	// Base coordinates
	int cx = 0;
	int cy = 0;
	float rx = 0;
	float ry = 0;

	// Resulting coordinates
	float xx = 0;
	float yy = 0;

	// Movements
	float dx = 0;
	float dy = 0;


	Game *game = nullptr;

	Entity(Game *g = nullptr) {
		sprite.setSize(sf::Vector2f(16, 64));
		sprite.setOrigin(sf::Vector2f(8, 64));
		radius = 16;
		game = g;
	}
	static float getMag(sf::Vector2f& vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}
	sf::Vector2f normalized(sf::Vector2f& vec) {
		return sf::Vector2f(vec.x / getMag(vec), vec.y / getMag(vec));
	}
	void SetPosition(sf::Vector2f pos) {
		SetPosition(pos.x, pos.y);
	}
	void SetPosition(int x, int y) {
		sprite.setPosition(sf::Vector2f(x, y));
		SetCoordinate(x, y);
	}
	sf::Vector2f GetPosition() {
		return sf::Vector2f(xx, yy);
	}
	sf::Vector2i GetPositionCase() {
		return sf::Vector2i(cx, cy);
	}
	sf::Vector2f GetSpeed() {
		return sf::Vector2f(dx, dy);
	}
	sf::Color GetColor() {
		return sprite.getFillColor();
	}

	void SetCoordinate(float x, float y);
	void SetCoordinate(sf::Vector2f pos);

	sf::Vector2f ConvertCoor(sf::Vector2f pos) {
		return sf::Vector2f(pos.x / GRID_SIZE, pos.y / GRID_SIZE);
	}
	void MoveX();
	void MoveY();
	void SetSpriteCoor();
	bool hasCollision(int nextX, int nextY);

	bool overlaps(Entity e);

	void Pushback(Entity e);

	virtual void UpdateEntity(double dt);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
};
