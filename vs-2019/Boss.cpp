//
// Boss.cpp
//

// Engine includes.
#include "EventStep.h"
#include "EventView.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "DataManager.h"
#include "GameManager.h"
#include <stdlib.h> /* rand */
#include <time.h>
#include "gameOver.h"

// Game includes.
#include "Boss.h"
#include "KillCounter.h"
#include "explosion.h"

Boss::Boss() {

	health = 10;

	// Basic zombie attributes.
	m_move_countdown = 0;
	m_think_countdown = 0;
	setType("Boss");
	setSolidness(df::SOFT);
	//Has HARD-like collisions with Soft Objects
	setNoSoft(true);
	setAltitude(3);
	setSpeed(0.25);

	LM.writeLog("BOSS SPAWN");

	// Default sprite
	setSprite("zombie-boss-r");
	facingRight = true;
	registerInterest(df::STEP_EVENT);

	// Keeps track of hero.
	p_hero = DATA.getHero();

	//determine the zombie's position
	determinePosition();

}

Boss::~Boss() {
	GM.setGameOver();
}

void Boss::determinePosition() {
	//Set the position of the zombie
	float X = WM.getBoundary().getHorizontal()/2;
	float Y = WM.getBoundary().getVertical()/2;
	float xPos = X;
	float yPos = Y;

	LM.writeLog("xpos, ypos: %f, %f", xPos, yPos);

	df::Vector final_position;
	final_position.setXY(xPos, yPos);

	setPosition(final_position);
}

void Boss::setMoveCountdown(int new_move_countdown) {
	m_move_countdown = new_move_countdown;
}
int Boss::getMoveCountdown() {
	return m_move_countdown;
}
void Boss::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}
int Boss::getThinkCountdown() {
	return m_think_countdown;
}

// Start or stop animation.
void Boss::stopAnimation(bool stop) {
	df::Animation animation = getAnimation();
	if (stop)
	{
		if (animation.getSlowdownCount() != -1)
		{
			animation.setSlowdownCount(-1);
			animation.setIndex(0);
		}
	}
	else
	{
		if (animation.getSlowdownCount() == -1)
		{
			animation.setSlowdownCount(0);
			animation.setIndex(0);
		}
	}
	setAnimation(animation);
}

// Handle event.
// Return 0 if ignored, else 1
int Boss::eventHandler(const df::Event* e) {
	if (e->getType() == df::STEP_EVENT) {
		setChase();
		return 1;
	}
	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		return hit(p_c);
	}
	return 0;
}

//Sets the chasing direction and sprite for the zombie
void Boss::setChase() {
	df::Vector hero_loc = seeHero();
	//LM.writeLog("location is %f %f", p_hero->getPosition().getX(), p_hero->getPosition().getY());

	df::Vector movement = df::Vector(-hero_loc.getX(), -hero_loc.getY());
	movement.normalize();
	movement.scale(ZOMBIE_SPEED_CHASE);

	//reduce vertical movement to match horizontal movement
	movement.setY(movement.getY() * 0.55);
	setVelocity(movement);

	//change left/right sprite based on hero location
	if (!facingRight && this->getPosition().getX() < p_hero->getPosition().getX()) {
		setSprite("zombie-boss-r");
		facingRight = true;
	}
	else if (facingRight && this->getPosition().getX() > p_hero->getPosition().getX()) {
		setSprite("zombie-boss-l");
		facingRight = false;
	}
}

//code to be run for an object colliding with a zombie
int Boss::hit(const df::EventCollision* p_c) {
	// If Bullet...

	if (p_c->getObject1()->getType() == "Tombstone" || p_c->getObject1()->getType() == "LargeTombstone") {
		WM.markForDelete(p_c->getObject1());
	} else if (p_c->getObject2()->getType() == "Tombstone" || p_c->getObject2()->getType() == "LargeTombstone") {
		WM.markForDelete(p_c->getObject2());
	}

	int bull_num;
	if (p_c->getObject1()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject1());
		setHealth(health - 1);
		bull_num = 1;
	}
	if (p_c->getObject2()->getType() == "bullet") {
		WM.markForDelete(p_c->getObject2());
		setHealth(health - 1);
		bull_num = 2;
	}

	if (health == 0) {
		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		df::EventView ev(KILLCOUNT_STRING, 100, true);
		WM.onEvent(&ev);

		if (bull_num == 1) {
			WM.markForDelete(p_c->getObject2());
		} else { WM.markForDelete(p_c->getObject1()); }
		
		
	}
	
	return 1;
}


// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Boss::seeHero() {
	df::Vector dir = getPosition() - p_hero->getPosition();
	dir.normalize();
	return dir;
}

void Boss::setHealth(int new_health) {
	health = new_health;
}
