#include "Glob.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "hero.h"

Glob::Glob() {

	setSprite("bullet");
	setType("glob");
	// Set starting location, based on hero's position passed in.
	//setVelocity(to_hero);

	// Bullets move 1 space each game loop.
 // The direction is set when the Hero fires.
	setSpeed(1);

	// Make the globs soft so can pass through Hero.
	setSolidness(df::SOFT);
}

int Glob::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Glob::out() {
	WM.markForDelete(this);
}

// if wall is hit, mark glob for deletion
void Glob::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Wall") ||
		(p_collision_event->getObject2()->getType() == "Wall")) {

		if (p_collision_event->getObject1()->getType() == "glob") {
			WM.markForDelete(p_collision_event->getObject1());
		}
		else {
			WM.markForDelete(p_collision_event->getObject2());
		}
	}
}