#include "KillCounter.h"
#include "Event.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DataManager.h"
#include "Boss.h"

KillCounter::KillCounter() {
	setLocation(df::TOP_RIGHT);
	setViewString(KILLCOUNT_STRING);
	setColor(df::YELLOW);
}

KillCounter::~KillCounter() {
	DATA.setKillCounter(NULL);
}

int KillCounter::eventHandler(const df::Event* p_e) {

	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		if (this->getValue() == DATA.getGoalObject()->getValue()) {
			DATA.setOnlyGoalMessage("DEFEAT THE BOSS!");
			DATA.setBossCount(1);
			new Boss;
		}
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		//Spawn Zombies based on Kill Counter
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}