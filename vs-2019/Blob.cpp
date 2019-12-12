
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
#include "Blob.h"
#include "KillCounter.h"
#include "explosion.h"
#include "Revolver.h"
#include "SpeedItem.h"
#include "Glob.h"

#define BASE_SHOOT_COUNTDOWN 80
#define KILLS_UNTIL_SWITCH 10
#define HEALTH_MOD 15
#define STARTING_HEALTH 40

Blob::Blob() {

	// Basic plant attributes.
	shoot_countdown = BASE_SHOOT_COUNTDOWN;
	m_think_countdown = 0;
	is_defence_state = false;
	health = STARTING_HEALTH;
	setType("Blob");
	setSolidness(df::HARD);

	setAltitude(3);
	setSpeed(0.25);


	// Default sprite
	setSprite("blob");
	registerInterest(df::STEP_EVENT);

	// Keeps track of hero.
	p_hero = DATA.getHero();

	setPosition(df::Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical()*(0.4f)));

	DATA.resetKills();
	LM.writeLog("Placed Blob");

}


Blob::~Blob() {
}


void Blob::setShootCountdown(int new_move_countdown) {
	shoot_countdown = new_move_countdown;
}
int Blob::getShootCountdown() {
	return shoot_countdown;
}
void Blob::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}
int Blob::getThinkCountdown() {
	return m_think_countdown;
}


// Handle event.
// Return 0 if ignored, else 1
int Blob::eventHandler(const df::Event* e) {
	if (e->getType() == df::STEP_EVENT) {
		changeState();
		spit();
		return 1;
	}
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

void Blob::changeState() {
	if(is_defence_state && DATA.getKills() >= DATA.getGoalCount()){
		is_defence_state = false;
		setSprite("blob");
		DATA.setOnlyGoalMessage("Attack the Blob!");
	}
}

void Blob::spit() {
	if (shoot_countdown == 0) {
		if (is_defence_state) {
			for (double i = -0.5; i < 1; i += 0.5) {
				for (double j = -0.5; j < 1; j += 0.5) {
					//Dont create glob with 0,0 velocity
					if (i || j) {
						Glob* g = new Glob(5);
						g->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY()));
						g->setVelocity(df::Vector(i, j));
					}
				}
			}
		}
		else {

			df::Vector s = seeHero();
			Glob* g = new Glob(20);
			g->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY()));
			df::Vector movement = df::Vector(-s.getX(), -s.getY());
			movement.normalize();
			//reduce vertical movement to match horizontal movement
			movement.setY(movement.getY() * 0.55);
			g->setVelocity(movement);
		}
		shoot_countdown = BASE_SHOOT_COUNTDOWN;
	}
	else {
		shoot_countdown--;
	}
}

//code to be run for an object colliding with a zombie
int Blob::hit(const df::EventCollision* p_c) {
	// If Plant, ignore.
	if ((p_c->getObject1()->getType() == "plant") &&
		(p_c->getObject2()->getType() == "plant"))
		return 1;
	// If Bullet also do nothing
	if ((p_c->getObject1()->getType() == "bullet") ||
		(p_c->getObject2()->getType() == "bullet")) {

		if ((p_c->getObject1()->getType() == "bullet")) {
			WM.markForDelete(p_c->getObject1());
		}
		else {
			WM.markForDelete(p_c->getObject2());
		}
		//only attack if in defence state
		if (!is_defence_state) {
			health--;
			if (health <= 0) {
				DATA.setGate();
				WM.markForDelete(this);
			}else if (health % HEALTH_MOD == 0) {
				is_defence_state = true;
				setSprite("blob-def");
				DATA.resetKills();
				DATA.setGoalContent("Kill Zombies to Weaken the Blob!", KILLS_UNTIL_SWITCH);
			}

		}
		return 1;
	}
	return 0;
}


// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Blob::seeHero() {
	if (p_hero == NULL) {
		return df::Vector(0, 0);
	}
	else {
		df::Vector dir = getPosition() - p_hero->getPosition();
		dir.normalize();
		return dir;
	}
}
