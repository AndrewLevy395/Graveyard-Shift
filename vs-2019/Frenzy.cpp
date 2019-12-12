
// Engine includes.
#include "EventStep.h"
#include "EventView.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "DataManager.h"
#include <stdlib.h> /* rand */
#include <time.h>

// Game includes.
#include "Frenzy.h"
#include "KillCounter.h"
#include "explosion.h"
#include "Revolver.h"
#include "SpeedItem.h"
#include "Glob.h"

#define BASE_SHOOT_COUNTDOWN 52;

Frenzy::Frenzy() {

	// Basic plant attributes.
	shoot_countdown = BASE_SHOOT_COUNTDOWN;
	m_think_countdown = 0;
	setType("Frenzy");
	setSolidness(df::HARD);

	setAltitude(3);
	setSpeed(0.25);


	// Default sprite
	setSprite("frenzy");
	registerInterest(df::STEP_EVENT);

	// Keeps track of hero.
	p_hero = DATA.getHero();

	setPosition(df::Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));
	LM.writeLog("Placed Frenzy");

}


Frenzy::~Frenzy() {
}


void Frenzy::setShootCountdown(int new_move_countdown) {
	shoot_countdown = new_move_countdown;
}
int Frenzy::getShootCountdown() {
	return shoot_countdown;
}
void Frenzy::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}
int Frenzy::getThinkCountdown() {
	return m_think_countdown;
}


// Handle event.
// Return 0 if ignored, else 1
int Frenzy::eventHandler(const df::Event* e) {
	if (e->getType() == df::STEP_EVENT) {
		spit();
		return 1;
	}
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

void Frenzy::spit() {
	if (shoot_countdown == 0) {
		df::Vector s = seeHero();
		Glob* g;
		for (int i = -1; i < 2; i++) {
			g = new Glob(60);
			g->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY()+i));
			df::Vector movement = df::Vector(-s.getX(), -s.getY());
			movement.normalize();
			//reduce vertical movement to match horizontal movement
			movement.setY(movement.getY() * 0.5);
			g->setVelocity(movement);
		}
		shoot_countdown = BASE_SHOOT_COUNTDOWN;
	}
	else {
		shoot_countdown--;
	}
}

//code to be run for an object colliding with a zombie
int Frenzy::hit(const df::EventCollision* p_c) {
	// If Plant, ignore.
	if ((p_c->getObject1()->getType() == "plant") &&
		(p_c->getObject2()->getType() == "plant"))
		return 1;
	// If Bullet also do nothing
	if ((p_c->getObject1()->getType() == "bullet") ||
		(p_c->getObject2()->getType() == "bullet")) {
		return 1;
	}
	return 0;
}


// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Frenzy::seeHero() {
	if (p_hero == NULL) {
		return df::Vector(0, 0);
	}
	else {
		df::Vector dir = getPosition() - p_hero->getPosition();
		dir.normalize();
		return dir;
	}
}
