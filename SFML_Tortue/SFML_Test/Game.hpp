#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <sys/stat.h>
#include <ctime>
#include "Lib.hpp"
#include "Tortue.hpp"

enum Commands { AVANCE_30, RECULE_30, TOURNER_GAUCHE_45, TOURNER_DROITE_45, DESSIN_ACTIVE, DESSIN_DESACTIVE };

class Game {
public:
	sf::RenderWindow* win;

	Tortue tortue;

	bool writing = false;

	FILE* cfile = nullptr;
	struct stat file_details;
	time_t latestModifiedTime;
	int frameCount = 6;
	int nextMove = -1;
	Game(sf::RenderWindow* win){
		//Get RenderWindow
		this->win = win;
		Tortue tmp;
		tortue = tmp;
		errno_t errRead = fopen_s(&cfile, "../res/command.txt", "r");
		stat("../res/command.txt", &file_details);
		latestModifiedTime = file_details.st_mtime;
	}

	void processInput(sf::Event event) {
		if (writing) {
			if (event.type == sf::Event::KeyPressed) {
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
					frameCount = 0;
				}
				/*if (event.key.code == sf::Keyboard::E) {
					if (tortue.draw) {
						fprintf(cfile, "%i", DESSIN_DESACTIVE);
					}
					else {
						fprintf(cfile, "%i", DESSIN_ACTIVE);
					}
					fprintf(cfile, "\n");
				}*/
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
	void ReadFile() {
		fscanf_s(cfile, "%i", &nextMove);
		frameCount = 0;
		TortueAction();
	}

	void TortueAction() {
		switch (nextMove) {
		case AVANCE_30:
			tortue.MoveForward(frameCount);
			break;
		case RECULE_30:
			tortue.MoveBackward();
			break;
		case TOURNER_GAUCHE_45:
			tortue.RotateTortue(-45);
			break;
		case TOURNER_DROITE_45:
			tortue.RotateTortue(45);
			break;
			/*case DESSIN_ACTIVE:
				tortue.ChangeDraw(true);
				break;
			case DESSIN_DESACTIVE:
				tortue.ChangeDraw(false);
				break;*/
		default:
			fclose(cfile);
			errno_t err = fopen_s(&cfile, "../res/command.txt", "w");
			stat("../res/command.txt", &file_details);
			latestModifiedTime = file_details.st_mtime;
			writing = true;
			break;
		}
	}

	void Update(double deltaTime) {
		if (writing) {
			/*stat("../res/command.txt", &file_details);
			time_t modifiedTime = file_details.st_mtime;
			if (latestModifiedTime != modifiedTime) {
				fclose(cfile);
				errno_t err = fopen_s(&cfile, "../res/command.txt", "r");
				writing = false;
			}*/
			pollInput(deltaTime);
		}
		else if (frameCount > 5) {
			ReadFile();
		}
		else {
			frameCount++;
			TortueAction();
		}
	}

	void draw() {
		tortue.drawTortue(win);
	}
};