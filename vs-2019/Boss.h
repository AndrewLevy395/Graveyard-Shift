
#ifndef BOSS_H
#define BOSS_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"
#include "EventCollision.h"
#include "hero.h"


const float ZOMBIE_SPEED_CHASE = 0.15;

class Boss : public df::Object {

private:
	Hero* p_hero;
	int m_move_countdown;
	int m_think_countdown;
	int health;
	enum direction_type direction;
	bool facingRight;
	void determinePosition();
	void setChase();
	int hit(const df::EventCollision* p_c);

public:
	Boss();
	~Boss();
	int eventHandler(const df::Event* e);
	void stopAnimation(bool stop);
	df::Vector seeHero();
	int getMoveCountdown();
	void setMoveCountdown(int new_move_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
	void setHealth(int new_health);
};
#endif
