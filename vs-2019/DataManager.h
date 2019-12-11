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
	int current_level;
	int numGas;
	int bossCount;
	Hero* p_hero;
	df::ViewObject* goal;
	df::Music* level_music;
	df::ViewObject* kill_counter;

	//places the objects for level 2
	void placeLevel2Objects();

	//places the objects for level 3
	void placeLevel3Objects();

public:
	//places the enemies for level 2
	void placeLevel2Enemies(bool atGenerator);

	// Get the one and only instance of the InputManager.
	static DataManager& getInstance();

	// Get terminal ready to capture input.
	// Return 0 if ok, else return -1.
	int startUp();

	// Revert back to normal terminal mode.
	void shutDown();

	//removes all objects with given type
	void removeAll(std::string type);

	//produces an exit to transition to the next level
	void transitionToNextLevel();

	//places the gate object on the map
	void setGate();

	Hero* getHero();

	void setHero(Hero* hero_pointer);

	df::ViewObject* getGoalObject();

	void setGoalObject(df::ViewObject* new_goal);

	void setGoalContent(std::string message, int value);

	std::string getGoalString();

	int getGoalCount();

	void setOnlyGoalMessage(std::string);

	void placeObject(df::Object* p_o);

	void setLevelMusic(df::Music* music);

	df::Music* getLevelMusic();

	void setKillCounter(df::ViewObject* kc);

	df::ViewObject* getKillCounter();

	void addGas();

	int getNumGas();

	int getBossCount();

	void setBossCount(int count);

	int getCurrentLevel();

	void determinePosition(df::Object* p_o, int position);

	void placeOuterWalls();
};

#endif