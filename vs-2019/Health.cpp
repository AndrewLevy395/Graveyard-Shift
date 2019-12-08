//
// Health.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "GameManager.h"	
#include "WorldManager.h"
#include "DataManager.h"

// Game includes.
#include "Health.h"

Health::Health() {
	setViewString(HEALTH_STRING);
	setColor(df::YELLOW);
	setLocation(df::TOP_LEFT);
	setValue(150);
}

// Handle event.
// Return 0 if ignored, else 1.
int Health::eventHandler(const df::Event* p_e) {
	// Call parent handler.
	if (df::ViewObject::eventHandler(p_e)) {
		if (getValue() < 1) {
			setValue(0);
			WM.markForDelete(DATA.getHero());
		}
			//df::GameManager::getInstance().setGameOver();
	}

	// If we get here, event not handled.
	return 0;
}
