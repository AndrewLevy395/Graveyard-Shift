
#ifndef BLOB_H
#define BLOB_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "StateMachine.h"
#include "EventCollision.h"

#include "hero.h"


class Blob : public df::Object {

private:
	Hero* p_hero;
	int shoot_countdown;
	int m_think_countdown;
	int health;
	bool is_defence_state;
	void changeState();
	void spit();
	int hit(const df::EventCollision* p_c);
	df::Vector seeHero();

public:
	Blob();
	~Blob();
	int eventHandler(const df::Event* e);
	int getShootCountdown();
	void setShootCountdown(int new_shoot_countdown);
	int getThinkCountdown();
	void setThinkCountdown(int new_think_countdown);
};
#endif
