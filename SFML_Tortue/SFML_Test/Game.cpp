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
	return END;
}

void Game::ReadFile(double dt) {
	nextMove = END;
	char moveString[40] = "";
	int retVal = fscanf(cfile, "%s", moveString);
	nextMove = StringToEnum(moveString);
	TortueAction(dt);
}

void Game::TortueAction(double dt) {
	switch (nextMove) {
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
	default:
		fclose(cfile);
		reading = false;
		break;
	}
}
