#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__
#include "Manager.h"
#include "hero.h"

#define DATA DataManager::getInstance()


class DataManager : public df::Manager {

private:
	DataManager();
	DataManager(DataManager const&);
	void operator=(DataManager const&);
	Hero* p_hero;

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
};

#endif