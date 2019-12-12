#include "hero.h"
#include "gameOver.h"
#include "bullet.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "WorldManager.h"
#include "DataManager.h"
#include "Glob.h"


#define BASE_FIRE_SLOWDOWN 10;
#define BASE_HERO_SPEED df::Vector(0.33f, 0.15f);

Hero::Hero() {
	// Link to "hero" sprite.
	setSprite("hero-r");
	stopAnimation(true);
	setNoSoft(true);
	facingRight = true;

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);


	setType("hero");
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	nuke_count = 1;

	move_slowdown = 2;
	move_countdown = move_slowdown;

	fire_slowdown = BASE_FIRE_SLOWDOWN;
	fire_countdown = fire_slowdown;

	hero_speed = BASE_HERO_SPEED;

	// Create reticle for firing bullets.
	p_reticle = new Reticle();
	p_reticle->draw();
}

Hero::~Hero() {
	// Create GameOver object.
	if (!DATA.gameEnded) {
		new GameOver;
	}
	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);

	// Make a big explosion with particles.
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

	//Add screenshake
	DM.shake(20, 20, 10);

	DATA.setHero(NULL);
}

void Hero::setFacingRight(bool is_right) {
	if (is_right && facingRight || !is_right && !facingRight) {
		return;
	}

	facingRight = is_right;

	if (facingRight) {
		setSprite("hero-r");
	}
	else {
		setSprite("hero-l");
	}
}

bool Hero::isFacingRight() {
	return facingRight;
}

int Hero::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT){
		const df::EventCollision* p_collision_event = (const df::EventCollision*)(p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Hero::hit(const df::EventCollision* p_c) {
	if (p_c->getObject1()->getType() == "Zombie" ||
		p_c->getObject2()->getType() == "Zombie"){
		// Send "view" event to Heath HUD indicating damage.
		df::EventView ev("Health", -1, true);
		WM.onEvent(&ev);
	}

	if (p_c->getObject1()->getType() == "Boss" ||
		p_c->getObject2()->getType() == "Boss") {
		// Send "view" event to Heath HUD indicating damage.
		df::EventView ev("Health", -1, true);
		WM.onEvent(&ev);
	}

	if (p_c->getObject1()->getType() == "glob"){
		Glob* glob = (Glob*)(p_c->getObject1());
		// Send "view" event to Heath HUD indicating damage.
		df::EventView ev("Health", -glob->getDamage(), true);
		WM.onEvent(&ev);
		WM.markForDelete(p_c->getObject1());
	}
	else if(p_c->getObject2()->getType() == "glob") {
		Glob* glob = (Glob*)(p_c->getObject2());
		df::EventView ev("Health", -glob->getDamage(), true);
		WM.onEvent(&ev);
		WM.markForDelete(p_c->getObject2());

	}

	if (p_c->getObject1()->getType() == "Revolver"){
		WM.markForDelete(p_c->getObject1());
		//Get Firing Speed boost
		fire_slowdown = 5;
	}
	else if (p_c->getObject2()->getType() == "Revolver") {
		WM.markForDelete(p_c->getObject2());
		//Get firing Speed Boost
		fire_slowdown = 5;
	}

	if (p_c->getObject1()->getType() == "SpeedItem") {
		WM.markForDelete(p_c->getObject1());
		hero_speed = df::Vector(0.50f, 0.25f);
	}
	else if (p_c->getObject2()->getType() == "SpeedItem") {
		WM.markForDelete(p_c->getObject2());
		hero_speed = df::Vector(0.50f, 0.25f);
	}

	if (p_c->getObject1()->getType() == "gas") {
		WM.markForDelete(p_c->getObject1());
		DATA.addGas();
	}
	else if (p_c->getObject2()->getType() == "gas") {
		WM.markForDelete(p_c->getObject2());
		DATA.addGas();
	}
	if (p_c->getObject1()->getType() == "HealthItem") {
		WM.markForDelete(p_c->getObject1());
		df::EventView ev("Health", 50, true);
		WM.onEvent(&ev);
	}
	else if (p_c->getObject2()->getType() == "HealthItem") {
		WM.markForDelete(p_c->getObject2());
		df::EventView ev("Health", 50, true);
		WM.onEvent(&ev);
	}

}

// Start or stop animation.
void Hero::stopAnimation(bool stop)
{
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

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::W:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED || 
			p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			df::Vector v(getVelocity().getX(), -hero_speed.getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(getVelocity().getX(), 0);
			setVelocity(v);
		}
		break;
	case df::Keyboard::S:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED || 
			p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			df::Vector v(getVelocity().getX(), hero_speed.getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(getVelocity().getX(), 0);
			setVelocity(v);
		}
		break;
	case df::Keyboard::A:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED || 
			p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			setFacingRight(false);
			df::Vector v(-hero_speed.getX(), getVelocity().getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(0, getVelocity().getY());
			setVelocity(v);
		}
		break;
	case df::Keyboard::D:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED || 
			p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			setFacingRight(true);
			df::Vector v(hero_speed.getX(), getVelocity().getY());
			setVelocity(v);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			df::Vector v(0, getVelocity().getY());
			setVelocity(v);
		}
		break;
	default:
		break;
	};

	// If not moving, stop animation.
	if (getSpeed() == 0)
		stopAnimation(true);
	else
		stopAnimation(false);

	return;
}

// Move up or down.
void Hero::move(int dy) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical()))
		WM.moveObject(this, new_pos);
}

// Decrease rate restriction counters.
void Hero::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

  // Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

void Hero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(this);
	p->setVelocity(v);

	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}
// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
}

void Hero::resetPowerups() {
	hero_speed = BASE_HERO_SPEED;
	fire_slowdown = BASE_FIRE_SLOWDOWN;
}

