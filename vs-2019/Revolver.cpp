
// Engine includes.
#include "GameManager.h"
#include "LogManager.h"

// Game includes.
#include "Revolver.h"

Revolver::Revolver() {
	setSprite("revolver");
	setSolidness(df::SOFT);
	setAltitude(1);
	setType("Revolver");
}

int Revolver::eventHandler(const df::Event* e) {

	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = static_cast <const df::EventCollision*> (e);
		hit(p_collision_event);
		return 1;
	}

	// If we get here, we have ignored this event.
	return 0;
}

void Revolver::hit(const df::EventCollision* p_c) {
	LM.writeLog("Revolver::hit(): Collision with '%s'",
		p_c->getObject1()->getType().c_str());
}
