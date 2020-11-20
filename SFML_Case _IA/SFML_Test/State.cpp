#include "State.hpp"
void JumpState::updateState() {
	e->jumpState();
}

void RunningState::updateState() {
	e->MoveX();
	e->MoveY();
}