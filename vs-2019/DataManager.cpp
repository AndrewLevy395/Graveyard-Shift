#include "DataManager.h"
#include "WorldManager.h"
#include <time.h> 


//override for assignment prevention
void DataManager::operator=(DataManager const&) {}

DataManager::DataManager() {
	p_hero = NULL;
	goal = NULL;
	setType("DataManager");
}

int DataManager::startUp() {
	return Manager::startUp();
}

void DataManager::shutDown() {
	return Manager::shutDown();
}

void DataManager::setHero(Hero* hero) {
	p_hero = hero;
}

Hero* DataManager::getHero() {
	return p_hero;
}

void DataManager::setGoalObject(df::ViewObject* new_goal) {
	goal = new_goal;
}

df::ViewObject* DataManager::getGoalObject() {
	return goal;
}

DataManager& DataManager::getInstance() {
	static DataManager datam;
	return datam;
}


void DataManager::setGoalContent(std::string message, int value) {
	goal->setDrawValue(true);
	goal->setViewString(message);
	goal->setValue(value);
}

std::string DataManager::getGoalString() {
	return goal->getViewString();
}

void DataManager::setOnlyGoalMessage(std::string message) {
	goal->setViewString(message);
	goal->setDrawValue(false);
}

// Randomly place Object, making sure no collision.
void DataManager::placeObject(df::Object* p_o) {

	// World dimensions (X,Y).
	int X = (int)WM.getBoundary().getHorizontal();
	int Y = (int)WM.getBoundary().getVertical();

	// Repeat until random (x,y) doesn't have collision for Object.
	df::ObjectList collision_list;
	df::Vector pos;
	srand(time(NULL));
	do {
		float x = (float)(rand() % (X - 8) + 4);
		float y = (float)(rand() % (Y - 4) + 2 + 1);
		pos.setXY(x, y);
		collision_list = WM.getCollisions(p_o, pos);
	} while (!collision_list.isEmpty());

	// Set position.
	p_o->setPosition(pos);
}