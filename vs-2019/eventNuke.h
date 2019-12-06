#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

const std::string NUKE_EVENT = "nuke";

class EventNuke : public df::Event {

public:
	EventNuke();
};