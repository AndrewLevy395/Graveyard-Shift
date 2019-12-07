#include "gameStart.h"
#include "hero.h"
#include "points.h"
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DataManager.h"
#include "Zombie.h"
#include "Wall.h"

GameStart::GameStart() {
	// Put in center of window.
	setLocation(df::CENTER_CENTER);
	setSprite("GameStart");
	setType("GameStart");
	registerInterest(df::KEYBOARD_EVENT);

	// Play start music.
	p_music = RM.getMusic("start music");
	playMusic();
}

int GameStart::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P: 			// play
			start();
			break;
		case df::Keyboard::Q:			// quit
			GM.setGameOver();
			break;
		default: // Key is not handled.
			break;
		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

void GameStart::start() {

	DATA.setHero(new Hero());

	for (int i = 0; i < NUM_ZOMBIES; i++) {
		new Zombie;
	}

	// Setup heads-up display.
	new Points;	// points display

	df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.
	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(1);
	p_vo->setColor(df::YELLOW);

	// World dimensions (X,Y).
	float X = WM.getBoundary().getHorizontal();
	float Y = WM.getBoundary().getVertical();

	// Place outer Walls.
	Wall* p_wall;
	p_wall = new Wall((int)X, 1);
	p_wall->setPosition(df::Vector(X / 2.0f, 1));
	p_wall = new Wall((int)X, 1);
	p_wall->setPosition(df::Vector(X / 2.0f, Y - 1));
	p_wall = new Wall(1, (int)Y - 1);
	p_wall->setPosition(df::Vector(0, Y / 2.0f));
	p_wall = new Wall(1, (int)Y - 1);
	p_wall->setPosition(df::Vector(X - 1, Y / 2.0f));

	// When game starts, become inactive.
	setActive(false);
	// Pause start music.
	p_music->pause();
}

// Override default draw so as not to display "value".
int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic() {
	p_music->play();
}