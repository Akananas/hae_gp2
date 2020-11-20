#pragma once
#include "Entity.hpp"
class Entity;
class State {
public:
	Entity* e = nullptr;
	State() {
	}
	State(Entity* ent) {
		e = ent;
	}
	virtual void updateState() = 0;
};
class JumpState : public State {
public:
	JumpState(Entity* ent) {
		e = ent;
	}
	virtual void updateState() override;
};
class RunningState : public State {
public:
	RunningState(Entity* ent) {
		e = ent;
	}
	virtual void updateState() override;
};