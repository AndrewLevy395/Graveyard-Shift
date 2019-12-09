#include "DataManager.h"
#include "WorldManager.h"
#include "Music.h"
#include "Gate.h"
#include "Wall.h"
#include "Plant.h"
#include "Frenzy.h"

//override for assignment prevention
void DataManager::operator=(DataManager const&) {}

DataManager::DataManager() {
	p_hero;
	goal;
	level_music;
	current_level = 1;
	setType("DataManager");
}

int DataManager::startUp() {
	return Manager::startUp();
}

void DataManager::shutDown() {
	return Manager::shutDown();
}

void DataManager::removeAll(std::string type) {
	df::ObjectList allObjects = WM.getAllObjects();
	df::ObjectListIterator it(&allObjects);
	for (it.first(); !it.isDone(); it.next()) {
		df::Object* p_o = it.currentObject();
		if (p_o->getType() == type) {
			WM.markForDelete(p_o);
		}
	}
}

void DataManager::transitionToNextLevel() {
	if (current_level == 1) {

		current_level = 2;
		df::Vector p(7, WM.getBoundary().getVertical() / 2);
		p_hero->setPosition(p);
		p_hero->resetPowerups();
		removeAll("Gate");
		placeLevel2Walls();
		placeLevel2Enemies(true);
		setGoalContent("Collect Gas Canisters", 4);
	}
	
}

void DataManager::setGate() {
	DATA.removeAll("Zombie");
	df::Vector placement(WM.getBoundary().getHorizontal()-3, WM.getBoundary().getVertical()/2);
	new Gate(placement);
	setOnlyGoalMessage("Escape to the Exit!");
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
	do {
		float x = (float)(rand() % (X - 8) + 4);
		float y = (float)(rand() % (Y - 4) + 2 + 1);
		pos.setXY(x, y);
		collision_list = WM.getCollisions(p_o, pos);
	} while (!collision_list.isEmpty());

	// Set position.
	p_o->setPosition(pos);
}

//sets the level music
void DataManager::setLevelMusic(df::Music* music) {
	level_music = music;
}

//returns the level music
df::Music* DataManager::getLevelMusic() {
	return level_music;
}

void DataManager::setKillCounter(df::ViewObject* kc) {
	kill_counter = kc;
}

df::ViewObject* DataManager::getKillCounter() {
	return kill_counter;
}

void DataManager::placeLevel2Walls() {
	Wall* wall;
	float w = WM.getBoundary().getHorizontal();
	float h = WM.getBoundary().getVertical();

	float farFromLeft = w * (0.20f);
	float farFromRight = w * (0.8f);
	float farFromTop = h * (0.3f);
	float farFromBot = h * (0.7f);

	//top left///////////////////////////////////
	df::Vector tl_1(farFromLeft / 2.0f, farFromTop); //bottom
	wall = new Wall(farFromLeft, 1);
	wall->setPosition(tl_1);

	df::Vector tl_2(farFromLeft, farFromTop); //side
	wall = new Wall(1, 4);
	wall->setPosition(tl_2);

	//Top center////////////////////////////////
	df::Vector ts(w / 2.0f, farFromTop-2.0f);
	wall = new Wall(22, 1);
	wall->setPosition(ts);

	//top right//////////////////////////////////
	df::Vector tr_1(farFromRight + 3.0f, farFromTop); //bottom
	wall = new Wall(6, 1);
	wall->setPosition(tr_1);

	df::Vector tr_2(farFromRight, farFromTop); //side
	wall = new Wall(1, 4);
	wall->setPosition(tr_2);

	//right center/////////////////////////////////
	df::Vector rc(farFromRight, h/2.0f); //side
	wall = new Wall(1, 2);
	wall->setPosition(rc);

	//bot right///////////////////////////////////
	df::Vector br_1(farFromRight + 3.0f, farFromBot); //bottom
	wall = new Wall(6, 1);
	wall->setPosition(br_1);

	df::Vector br_2(farFromRight, farFromBot); //side
	wall = new Wall(1, 4);
	wall->setPosition(br_2);


	//Bot center////////////////////////////////
	df::Vector bs(w / 2.0f, farFromBot+2.0f);
	wall = new Wall(22, 1);
	wall->setPosition(bs);

	//bot left////////////////////////////////////
	df::Vector bl_1(farFromLeft / 2.0f, farFromBot); //bottom
	wall = new Wall(farFromLeft, 1);
	wall->setPosition(bl_1);

	df::Vector bl_2(farFromLeft, farFromBot); //side
	wall = new Wall(1, 4);
	wall->setPosition(bl_2);
}

void DataManager::placeLevel2Enemies(bool atGenerator) {
	float w = WM.getBoundary().getHorizontal();
	float h = WM.getBoundary().getVertical();
	if (atGenerator) {
		new Plant(df::Vector(4, 3));
	}
	new Plant(df::Vector(w-4, 3));
	new Plant(df::Vector(4, h-3));
	new Plant(df::Vector(w-4, h-3));

	new Frenzy();
}