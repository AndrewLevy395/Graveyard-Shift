#include "gameOver.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "gameStart.h"

GameOver::GameOver() {
	setType("GameOver");
	// Link to "message" sprite.
	if (setSprite("GameOver") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;
	// Put in center of window.
	setLocation(df::CENTER_CENTER);

	// Register for step event.
	registerInterest(df::STEP_EVENT);

	// Play "game over" sound.
	df::Sound* p_sound = RM.getSound("scream");
	p_sound->play();

}

// When object exits, indicate game over.
GameOver::~GameOver() {
	GM.setGameOver();
}

int GameOver::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

// Count down to end of message.
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

// Override default draw so as not to display "value".
int GameOver::draw() {
	return df::Object::draw();
}