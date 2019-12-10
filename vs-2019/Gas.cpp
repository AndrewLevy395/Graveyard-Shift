#include "Gas.h"

Gas::Gas(df::Vector position) {
	setSolidness(df::SOFT);
	setSprite("gas");
	setType("gas");
	setPosition(position);
}