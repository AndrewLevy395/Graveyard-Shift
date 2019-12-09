
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
#include "Plant.h"
#include "KillCounter.h"
#include "explosion.h"
#include "Revolver.h"
#include "SpeedItem.h"
#include "Glob.h"

Plant::Plant(df::Vector position) {

	// Basic plant attributes.
	shoot_countdown = 10;
	m_think_countdown = 0;
	setType("Plant");
	setSolidness(df::HARD);

	setAltitude(3);
	setSpeed(0.25);


	// Default sprite
	setSprite("plant");
	registerInterest(df::STEP_EVENT);

	// Keeps track of hero.
	p_hero = DATA.getHero();

	setPosition(position);
	LM.writeLog("Placed Plant");

}


Plant::~Plant() {
	if (DATA.getKillCounter() != NULL) {
		if (DATA.getKillCounter()->getValue() == 10) {
			Revolver* r = new Revolver();
			df::Vector v = this->getPosition();
			v.setY(v.getY() + 3);
			r->setPosition(v);
		}
	}
	srand(time(NULL));
	int randNum = rand() % 20 + 1;
	if (randNum == 5) {
		SpeedItem* s = new SpeedItem();
		s->setPosition(this->getPosition());
		LM.writeLog("MADE A SPEED");
	}

	// Create an explosion.
	Explosion* p_explosion = new Explosion;
	p_explosion->setPosition(this->getPosition());
}


void Plant::setShootCountdown(int new_move_countdown) {
	shoot_countdown = new_move_countdown;
}
int Plant::getShootCountdown() {
	return shoot_countdown;
}
void Plant::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}
int Plant::getThinkCountdown() {
	return m_think_countdown;
}


// Handle event.
// Return 0 if ignored, else 1
int Plant::eventHandler(const df::Event* e) {
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

void Plant::spit() {
	if (shoot_countdown == 0) {
		df::Vector s = seeHero();
		if (s.getX() || s.getY()) {
			Glob* g = new Glob();
			g->setPosition(this->getPosition());

			df::Vector movement = df::Vector(-s.getX(), -s.getY());
			movement.normalize();
			//movement.scale(ZOMBIE_SPEED_CHASE);

			//reduce vertical movement to match horizontal movement
			movement.setY(movement.getY() * 0.55);
			g->setVelocity(movement);



			//g->setVelocity(s);
			shoot_countdown = 10;
		}
	}
	else {
		shoot_countdown--;
	}
}

//code to be run for an object colliding with a zombie
int Plant::hit(const df::EventCollision* p_c) {
	// If Saucer on Saucer, ignore.
	if ((p_c->getObject1()->getType() == "Zombie") &&
		(p_c->getObject2()->getType() == "Zombie"))
		return 1;
	// If Bullet...
	if ((p_c->getObject1()->getType() == "bullet") ||
		(p_c->getObject2()->getType() == "bullet")) {


		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());

		df::EventView ev(KILLCOUNT_STRING, 1, true);
		WM.onEvent(&ev);

		return 1;
	}
	return 0;
}


// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Plant::seeHero() {

	//Returns a line between the plant's position and the hero's
	df::Line sight_line(getPosition(), p_hero->getPosition());

	//See if there are objects on the line via iterating through list
	df::ObjectList objectList = WM.objectsOnLine(sight_line);
	df::ObjectListIterator iterator(&objectList);


	bool found = false;
	for (iterator.first(); !iterator.isDone(); iterator.next()) {
		if (iterator.currentObject()->getType() == "Wall") {
			found = true;
		}
	}

	// If no wall found and in sense range, get direction of hero
	if (!found) {
		df::Vector dir = getPosition() - p_hero->getPosition();
		dir.normalize();
		return dir;
	}

	return df::Vector(0, 0); // False condition, cant see
}
