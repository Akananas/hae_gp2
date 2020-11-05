#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Tortue{
public:
	sf::CircleShape tortue;
	sf::RectangleShape direction;
	float pixelToMove = 0;
	float nextRotate = 0;
	float speed = 5;
	float rotSpeed = 2.5f;
	sf::VertexArray line;
	std::vector<sf::VertexArray> lines;
	bool draw = false;
	sf::Color pixelColor;
	Tortue(){
		tortue.setRadius(25);
		tortue.setFillColor(sf::Color::Green);
		tortue.setOrigin(25, 25);
		tortue.setPosition(300, 300);
		direction.setSize(sf::Vector2f(50, 8));
		direction.setOrigin(0, 4);
		direction.setPosition(tortue.getPosition());
		direction.setRotation(tortue.getRotation());
		line.setPrimitiveType(sf::LinesStrip);
		pixelColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	}
	bool GetNextMove() {
		if (pixelToMove <= 0 && nextRotate == 0) {
			return true;
		}
		return false;
	}
	void RotateTortue(float angle, double dt);

	void Move(double dt, int side);

	sf::Vector2f rotateVector(sf::Vector2f pos) {
		float angle = tortue.getRotation() * (3.14159 / 180.0);
		sf::Vector2f dir(cos(angle), sin(angle));
		return dir;
	}
	void ChangeDraw(bool val) {
		if (!val) {
			sf::VertexArray tmpLine = line;
			lines.push_back(tmpLine);
			line.clear();
		}
		else {
			pixelColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
			line.append(sf::Vertex(tortue.getPosition(), pixelColor));
		}
		draw = val;
	}
	void drawTortue(sf::RenderWindow* win) {
		win->draw(tortue);
		win->draw(direction);
		for (int i = 0; i < lines.size(); i++) {
			win->draw(lines[i]);
		}
		win->draw(line);
	}

};