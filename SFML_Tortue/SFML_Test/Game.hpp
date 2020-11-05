#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include "Tortue.hpp"
#include <vector>

enum Commands { AVANCE_30, RECULE_30, TOURNER_GAUCHE_45, TOURNER_DROITE_45, END };

class Game {
public:
	sf::RenderWindow* win;

	Tortue tortue;

	bool writing = false;

	FILE* cfile = nullptr;
	struct stat file_details;
	time_t latestModifiedTime;
	Commands nextMove;
	bool reading = false;

	std::vector<Commands> cmd;

	Game(sf::RenderWindow* win) {
		this->win = win;
	}

	void processInput(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			if (writing) {
				if (event.key.code == sf::Keyboard::Q) {
					fprintf(cfile, "%i", TOURNER_GAUCHE_45);
					fprintf(cfile, "\n");
					//tortue.RotateTortue(-45);
				}
				if (event.key.code == sf::Keyboard::D) {
					fprintf(cfile, "%i", TOURNER_DROITE_45);
					fprintf(cfile, "\n");
					//tortue.RotateTortue(45);
				}
				if (event.key.code == sf::Keyboard::Space) {
					fclose(cfile);
					errno_t err = fopen_s(&cfile, "../res/command.txt", "r");
					writing = false;
				}
			}
			if (event.key.code == sf::Keyboard::F) {
				errno_t errRead = fopen_s(&cfile, "../res/command.txt", "r");
				reading = true;
			}
		}
	}

	void pollInput(double dt) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			fprintf(cfile, "%i", AVANCE_30);
			fprintf(cfile, "\n");
			//tortue.MoveForward();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			fprintf(cfile, "%i", RECULE_30);
			fprintf(cfile, "\n");
			//tortue.MoveBackward();
		}
	}
	Commands StringToEnum(char moveName[]);

	void ReadFile(double dt);

	void TortueAction(double dt);

	void Update(double deltaTime) {
		if (writing) {
			pollInput(deltaTime);
		}
		else if (tortue.GetNextMove() && reading) {
			ReadFile(deltaTime);
		}
		else if(reading) {
			TortueAction(deltaTime);
		}
	}

	void draw() {
		win->draw(tortue);
	}
};