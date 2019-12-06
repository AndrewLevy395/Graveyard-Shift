#ifndef __HERO__
#define __HERO__
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "reticle.h"

const df::Vector HERO_SPEED(0.33f, 0.15f);

class Hero : public df::Object {

private:
	void stopAnimation(bool stop);
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dy);
	void step();
	void nuke();
	void mouse(const df::EventMouse* p_mouse_event);
	void fire(df::Vector target);
	void setFacingRight(bool is_right);
	bool facingRight;
	int move_slowdown;
	int move_countdown;
	int fire_slowdown;
	int fire_countdown;
	int nuke_count;
	Reticle* p_reticle;

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event* p_e);
	bool isFacingRight();
};
#endif 