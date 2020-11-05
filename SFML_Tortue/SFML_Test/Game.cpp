#include "Game.hpp"

Commands Game::StringToEnum(char moveName[]) {
	if (strcmp("AVANCE_30", moveName) == 0) {
		return AVANCE_30;
	}
	else if (strcmp(moveName, "RECULE_30") == 0) {
		return RECULE_30;
	}
	else if (strcmp(moveName, "TOURNER_GAUCHE_45") == 0) {
		return TOURNER_GAUCHE_45;
	}
	else if (strcmp(moveName, "TOURNER_DROITE_45") == 0) {
		return TOURNER_DROITE_45;
	}
	else if (strcmp(moveName, "DESSIN_ACTIVE") == 0) {
		return DESSIN_ACTIVE;
	}
	else if (strcmp(moveName, "DESSIN_DESACTIVE") == 0) {
		return DESSIN_DESACTIVE;
	}
	return END;
}

void Game::ReadFile() {
	while (true) {
		char moveString[40] = "";
		int retVal = fscanf(cfile, "%s", moveString);
		Commands curCmd = StringToEnum(moveString);
		cmd.push_back(curCmd);
		if (curCmd == END) {
			break;
		}
	}
	reading = true;
}

void Game::TortueAction(double dt) {
	switch (cmd[0]) {
	case AVANCE_30:
		tortue.Move(dt, 1);
		break;
	case RECULE_30:
		tortue.Move(dt, -1);
		break;
	case TOURNER_GAUCHE_45:
		tortue.RotateTortue(-45, dt);
		break;
	case TOURNER_DROITE_45:
		tortue.RotateTortue(45, dt);
		break;
	case DESSIN_ACTIVE:
		tortue.ChangeDraw(true);
		break;
	case DESSIN_DESACTIVE:
		tortue.ChangeDraw(false);
		break;
	default:
		fclose(cfile);
		reading = false;
		break;
	}
}
