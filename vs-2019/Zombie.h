
#ifndef ZOMBIE_H
#define ZOMBIE_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"
#include "EventCollision.h"

#include "hero.h"


const float ZOMBIE_SPEED_CHASE = 0.15;
const int NUM_ZOMBIES = 10;

class Zombie : public df::Object {

private:
	Hero* p_hero;
	int m_move_countdown;
	int m_think_countdown;
	enum direction_type direction;
	bool facingRight;
	void determinePosition();
	void setChase();
	int hit(const df::EventCollision* p_c);

public:
	Zombie();
	~Zombie();
	int eventHandler(const df::Event* e);
	void stopAnimation(bool stop);
	df::Vector seeHero();
	int getMoveCountdown();
	void setMoveCountdown(int new_move_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
};
#endif
