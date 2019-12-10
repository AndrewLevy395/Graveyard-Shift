//
// HealthItem.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "DataManager.h"
#include "EventStep.h"

// Game includes.
#include "HealthItem.h"

HealthItem::HealthItem() {
	setSprite("healthitem");
	setSolidness(df::SOFT);
	setAltitude(1);
	setType("HealthItem");
	registerInterest(df::STEP_EVENT);
}

int HealthItem::eventHandler(const df::Event* e) {

	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = static_cast <const df::EventCollision*> (e);
		hit(p_collision_event);
		return 1;
	}
	else {
		setSolidness(df::SOFT);
	}

	// If we get here, we have ignored this event.
	return 0;
}

void HealthItem::hit(const df::EventCollision* p_c) {
	if (p_c->getObject1()->getType() == "Zombie" || p_c->getObject2()->getType() == "Zombie") {
		setSolidness(df::SPECTRAL);
	}
	LM.writeLog("SpeedItem::hit(): Collision with '%s'",
		p_c->getObject1()->getType().c_str());
}
