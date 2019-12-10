//
// Largeombstone.cpp
//

#include "LargeTombstone.h"
#include "WorldManager.h"
#include "DataManager.h"

LargeTombstone::LargeTombstone() {
	setType("LargeTombstone");
	setSolidness(df::HARD);
	setNoSoft(true);
	setSprite("tombstone-large");
	LM.writeLog("large tombstone created");
}

int LargeTombstone::eventHandler(const df::Event* e) {
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

//code to be run for an object colliding with a zombie
int LargeTombstone::hit(const df::EventCollision* p_c) {
	if (p_c->getObject1()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject1());
	}

	if (p_c->getObject2()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject2());
	}
	return 1;
}

