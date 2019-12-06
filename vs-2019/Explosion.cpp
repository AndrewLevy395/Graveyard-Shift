#include "explosion.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"

Explosion::Explosion() {
	registerInterest(df::STEP_EVENT);

	// Link to "explosion" sprite.
	if (setSprite("explosion") == 0)
		// Set live time as long as sprite length.
		time_to_live = getAnimation().getSprite()->getFrameCount();
	else
		time_to_live = 0;

	setType("explosion");

	setSolidness(df::SPECTRAL);

}

//Decreases the time_to_live by 1 every step
void Explosion::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

int Explosion::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}