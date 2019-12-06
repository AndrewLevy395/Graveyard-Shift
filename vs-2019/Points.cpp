#include "points.h"
#include "Event.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);
	registerInterest(df::STEP_EVENT);
}

int Points::eventHandler(const df::Event* p_e) {

	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If step, increment score every second (30 steps).
	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast <const df::EventStep*> (p_e)
			->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}

		// If get here, have ignored this event.
		return 0;
}