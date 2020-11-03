#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Tortue {
public:
	sf::CircleShape tortue;
	sf::RectangleShape direction;
	sf::VertexArray line;
	vector<sf::VertexArray> lines;
	bool draw = false;
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
	}

	void RotateTortue(float angle) {
		tortue.rotate(angle);
		direction.setRotation(tortue.getRotation());
	}

	void MoveForward(int nextMove) {
		sf::Vector2f tortuePos = tortue.getPosition();
		sf::Vector2f dir = rotateVector(tortuePos);
		dir.x *= 20 * float(5 /nextMove);
		dir.y *= 20 * float(5 / nextMove);
		tortuePos.x += dir.x;
		tortuePos.y += dir.y;
		tortue.setPosition(tortuePos);
		direction.setPosition(tortuePos);
		if (draw) {
			line.append(sf::Vertex(tortuePos));
		}
	}
	void ChangeDraw(bool val) {
		sf::VertexArray tmpLine = line;
		lines.push_back(tmpLine);
		line.clear();
		draw = val;
	}
	void MoveBackward() {
		sf::Vector2f tortuePos = tortue.getPosition();
		sf::Vector2f dir = rotateVector(tortuePos);
		dir.x *= 20;
		dir.y *= 20;
		tortuePos.x -= dir.x;
		tortuePos.y -= dir.y;
		tortue.setPosition(tortuePos);
		direction.setPosition(tortuePos);
		if (draw) {
			line.append(sf::Vertex(tortuePos));
		}
	}

	void drawTortue(sf::RenderWindow* win) {
		win->draw(tortue);
		win->draw(direction);
		for (int i = 0; i < lines.size(); i++) {
			win->draw(lines[i]);
		}
	}

	sf::Vector2f rotateVector(sf::Vector2f pos) {
		float angle = tortue.getRotation() * (3.14159 / 180.0);
		sf::Vector2f dir(cos(angle), sin(angle));
		return dir;
	}
};