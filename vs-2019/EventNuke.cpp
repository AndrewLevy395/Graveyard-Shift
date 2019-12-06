#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "eventNuke.h"

EventNuke::EventNuke() {
	setType(NUKE_EVENT);
};