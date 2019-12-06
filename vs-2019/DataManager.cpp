#include "DataManager.h"

//override for assignment prevention
void DataManager::operator=(DataManager const&) {}

DataManager::DataManager() {
	p_hero = NULL;
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

DataManager& DataManager::getInstance() {
	static DataManager datam;
	return datam;
}