#include "Car.h"

Car::Car(df::Vector position) {
	setType("Car");
	setSprite("car");
	setPosition(position);
	setSolidness(df::HARD);
	setNoSoft(true);
}
