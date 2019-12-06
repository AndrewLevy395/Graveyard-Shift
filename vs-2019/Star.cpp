#include "star.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include <stdlib.h>

Star::Star() {
	setType("Star");
	setSolidness(df::SPECTRAL); //dont interact with other objects
	setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0)); //set random velocity for stars
	setAltitude(0);	// Make Stars in background.
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);
}

int Star::draw(void) {
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

int Star::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	return 0;
}

// If Star moved off window, move back to far right.
void Star::out() {
	df::Vector p((float)(WM.getBoundary().getHorizontal() + rand() % 20),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);
	setVelocity(df::Vector(-1.0 / (rand() % 10 + 1), 0));
}