//
// Tombstone.cpp
//

#include "Tombstone.h"
#include "WorldManager.h"

Tombstone::Tombstone() {
	setType("Tombstone");
	setSolidness(df::HARD);
	setNoSoft(true);
	setSprite("tombstone");
	LM.writeLog("tombstone created");
}

int Tombstone::eventHandler(const df::Event* e) {
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

//code to be run for an object colliding with a zombie
int Tombstone::hit(const df::EventCollision* p_c) {
	if (p_c->getObject1()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject1());
	}

	if (p_c->getObject2()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject2());
	}
	return 1;
}