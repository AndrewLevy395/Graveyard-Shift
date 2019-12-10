#include "gameStart.h"
#include "hero.h"
#include "KillCounter.h"
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DataManager.h"
#include "Zombie.h"
#include "Tombstone.h"
#include "Wall.h"
#include "Health.h"
#include "LargeTombStone.h"
#include "SpeedItem.h"

#define LEVEL_ONE_KILL_GOAL 25

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

	new LargeTombstone;
	

	for (int i = 0; i < NUM_ZOMBIES; i++) {
		new Zombie;
	}

	// Setup heads-up display.
	DATA.setKillCounter(new KillCounter());	// kill count display
	new Health; // add health

	df::ViewObject* p_vo = new df::ViewObject; // Kill Goal
	p_vo->setLocation(df::TOP_CENTER);
	p_vo->setViewString("KILL GOAL: ");
	p_vo->setValue(LEVEL_ONE_KILL_GOAL);
	p_vo->setColor(df::YELLOW);
	DATA.setGoalObject(p_vo);

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

	//Place tombstones.
	for (int i = 0; i < 5; i++)
		DATA.placeObject(new Tombstone);

	// When game starts, become inactive.
	setActive(false);


	// Pause start music.
	p_music->stop(); //->pause();

	//Set and play the level music
	df::Music* l_music = RM.getMusic("level music");
	DATA.setLevelMusic(l_music);
	l_music->play();
}

// Override default draw so as not to display "value".
int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic() {
	p_music->play();
}