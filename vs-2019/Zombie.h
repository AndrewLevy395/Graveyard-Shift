
#ifndef ZOMBIE_H
#define ZOMBIE_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"

#include "hero.h"


const float MUMMY_SPEED_CHASE = 0.25;
const float MUMMY_SPEED_COWER = 0.30;
const float MUMMY_SPEED_WANDER = 0.10;
const float MUMMY_SPEED_SEEK = 0.15;

class Zombie : public df::Object {

private:
	Hero* p_hero;
	int m_move_countdown;
	int m_think_countdown;
	enum direction_type direction;

public:
	Zombie();
	int eventHandler(const df::Event* e);
	void stopAnimation(bool stop);
	df::Vector seeHero();
	int getMoveCountdown();
	void setMoveCountdown(int new_move_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
};

#endif
