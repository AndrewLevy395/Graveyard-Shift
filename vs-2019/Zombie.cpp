//
// Mummy.cpp
//

// Engine includes.
#include "EventStep.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "DataManager.h"
#include "explosion.h"
#include <stdlib.h> /* rand */
#include <time.h>

// Game includes.
#include "Zombie.h"

Zombie::Zombie(){

	// Basic zombie attributes.
	m_move_countdown = 0;
	m_think_countdown = 0;
	setType("Saucer");
	setSolidness(df::HARD);
	setAltitude(3);
	setSpeed(1);


	// Default sprite
	setSprite("saucer");
	registerInterest(df::STEP_EVENT);

	// Keeps track of hero.
	p_hero = DATA.getHero();

	//determine the zombie's position
	determinePosition();
	
}

void Zombie::determinePosition() {
	//Set the position of the zombie
	float X = WM.getBoundary().getHorizontal();
	float Y = WM.getBoundary().getVertical();
	float xPos = X;
	float yPos = Y;
	float xOffset = 0;
	float yOffset = 0;

	//srand(time(NULL));
	int edge = 1;//rand() % 4 + 1; // 1-4


	if (edge == 1) { //left
		LM.writeLog("Left");
		xOffset = -1;
		xPos = -5.0;
		yPos = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / Y));
	}
	if (edge == 2) { //top
		LM.writeLog("Top");
		yOffset = 1;
		xPos = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X));
		yPos = Y + 5.0;
	}
	if (edge == 3) { //right
		LM.writeLog("Right");
		xOffset = 1;
		xPos = X + 5.0;
		yPos = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / Y));
	}
	if (edge == 4) { //bot
		LM.writeLog("Bot");
		yOffset = -1;
		xPos = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X));
		yPos = Y - 5.0;
	}
	LM.writeLog("xpos, ypos: %f, %f", xPos, yPos);

	df::Vector final_position;
	final_position.setXY(xPos, yPos);

	// If collision, move slightly away from stage until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, final_position);
	while (!collision_list.isEmpty()) {
		final_position.setXY(final_position.getX() + xOffset, final_position.getY() + yOffset);
		collision_list = WM.getCollisions(this, final_position);
	}


	setPosition(final_position);
}

void Zombie::setMoveCountdown(int new_move_countdown) {
	m_move_countdown = new_move_countdown;
}
int Zombie::getMoveCountdown() {
	return m_move_countdown;
}
void Zombie::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}
int Zombie::getThinkCountdown() {
	return m_think_countdown;
}

// Start or stop animation.
void Zombie::stopAnimation(bool stop) {
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
int Zombie::eventHandler(const df::Event* e) {
	if (e->getType() == df::STEP_EVENT)
	{
		df::Vector hero_loc = seeHero();
		//LM.writeLog("location is %f %f", p_hero->getPosition().getX(), p_hero->getPosition().getY());

		df::Vector movement = df::Vector(-hero_loc.getX(), -hero_loc.getY());
		movement.normalize();
		movement.scale(MUMMY_SPEED_CHASE);
		setVelocity(movement);
		return 1;
	}
	if (e->getType() == df::COLLISION_EVENT) {

		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);

		// If Saucer on Saucer, ignore.
		if ((p_c->getObject1()->getType() == "saucer") &&
			(p_c->getObject2()->getType() == "saucer"))
			return 1;
		// If Bullet...
		if ((p_c->getObject1()->getType() == "bullet") ||
			(p_c->getObject2()->getType() == "bullet")) {

			// Create an explosion.
			Explosion* p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			WM.markForDelete(p_c->getObject1());
			WM.markForDelete(p_c->getObject2());

			return 1;
		}
	}
	return 0;
}


// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Zombie::seeHero() {
	df::Vector dir = getPosition() - p_hero->getPosition();
	dir.normalize();
	return dir;
}
