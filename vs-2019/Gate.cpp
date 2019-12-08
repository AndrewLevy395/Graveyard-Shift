#include "Gate.h"
#include "WorldManager.h"
#include "DataManager.h"

Gate::Gate(df::Vector position) {
	setType("Gate");
	setSolidness(df::HARD);
	setSprite("gate");
	LM.writeLog("gate created");
	setPosition(position);
}

int Gate::eventHandler(const df::Event* e) {
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

//code to be run for an object colliding with a zombie
int Gate::hit(const df::EventCollision* p_c) {
	if (p_c->getObject1()->getType() == "hero"||
		p_c->getObject2()->getType() == "hero") {
		DATA.transitionToNextLevel();
	}
	return 1;
}