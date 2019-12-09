
#ifndef FRENZY_H
#define FRENZY_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"
#include "EventCollision.h"

#include "hero.h"


class Frenzy : public df::Object {

private:
	Hero* p_hero;
	int shoot_countdown;
	int m_think_countdown;
	void spit();
	int hit(const df::EventCollision* p_c);
	df::Vector seeHero();

public:
	Frenzy();
	~Frenzy();
	int eventHandler(const df::Event* e);
	int getShootCountdown();
	void setShootCountdown(int new_shoot_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
};
#endif
