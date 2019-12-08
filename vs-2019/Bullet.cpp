#include "bullet.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "hero.h"

Bullet::Bullet(Hero* hero) {

	setSprite("bullet");	
	setType("bullet");
	// Set starting location, based on hero's position passed in.
	int bullet_pos = hero->isFacingRight()? 3 : -3;
	df::Vector p(hero->getPosition().getX() + bullet_pos, hero->getPosition().getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
 // The direction is set when the Hero fires.
	setSpeed(1);

	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
}

int Bullet::eventHandler(const df::Event* p_e) {

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
void Bullet::out() {
	WM.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion. (Content moved to Suacer Hit)
void Bullet::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Wall") ||
		(p_collision_event->getObject2()->getType() == "Wall")) {

		if (p_collision_event->getObject1()->getType() == "bullet") {
			WM.markForDelete(p_collision_event->getObject1());
		}
		else {
			WM.markForDelete(p_collision_event->getObject2());
		}
	}
}