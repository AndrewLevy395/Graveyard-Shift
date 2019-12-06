// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "vs-2019/points.h"
#include "ResourceManager.h"
#include "vs-2019/hero.h"
#include "vs-2019/star.h"
#include "vs-2019/gameStart.h"
#include "Object.h"
#include "Pause.h"
#include <stdio.h>


void populateWorld(void) {
	// Spawn GameStart object.
	new GameStart();
}

void loadResources(void) {
	// Load saucer sprite.
	RM.loadSprite("sprites/saucer-spr.txt", "saucer");
	RM.loadSprite("sprites/tanker-spr.txt", "tanker");
	RM.loadSprite("sprites/hero-r-spr.txt", "hero-r");
	RM.loadSprite("sprites/hero-l-spr.txt", "hero-l");
	RM.loadSprite("sprites/cluster-spr.txt", "bullet");
	RM.loadSprite("sprites/cluster-spr.txt", "cluster");
	RM.loadSprite("sprites/explosion-spr.txt", "explosion");
	RM.loadSprite("sprites/gameover-spr.txt", "GameOver");
	RM.loadSprite("sprites/gamestart-spr.txt", "GameStart");
	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/scream.wav", "scream");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over.wav", "game over");
	RM.loadMusic("sounds/start-music.wav", "start music");
}

int main(int argc, char* argv[]) {

	// Start up Game Manager.
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	LM.setFlush(true);

	// Show splash screen.
	df::splash();

	// 
	loadResources();
	populateWorld();
	// Enable player to pause game.
	new df::Pause(df::Keyboard::F10);

	printf("STARTING-------------------------------");
	GM.run();

	// Shut everything down.
	GM.shutDown();
}
