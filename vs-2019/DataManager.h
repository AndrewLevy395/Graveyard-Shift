#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__
#include "Manager.h"
#include "ViewObject.h"
#include "hero.h"
#include "Music.h"
#include <string.h>

#define DATA DataManager::getInstance()


class DataManager : public df::Manager {

private:
	DataManager();
	DataManager(DataManager const&);
	void operator=(DataManager const&);
	Hero* p_hero;
	df::ViewObject* goal;
	df::Music* level_music;
	df::ViewObject* kill_counter;

public:
	// Get the one and only instance of the InputManager.
	static DataManager& getInstance();

	// Get terminal ready to capture input.
	// Return 0 if ok, else return -1.
	int startUp();

	// Revert back to normal terminal mode.
	void shutDown();

	Hero* getHero();

	void setHero(Hero* hero_pointer);

	df::ViewObject* getGoalObject();

	void setGoalObject(df::ViewObject* new_goal);

	void setGoalContent(std::string message, int value);

	std::string getGoalString();

	void setOnlyGoalMessage(std::string);

	void placeObject(df::Object* p_o);

	void setLevelMusic(df::Music* music);

	df::Music* getLevelMusic();

	void setKillCounter(df::ViewObject* kc);

	df::ViewObject* getKillCounter();
};

#endif