#include "Object.h"
#include "ViewObject.h"
#include "Event.h"

#define KILLCOUNT_STRING "KILLS:"

class KillCounter : public df::ViewObject {

public:
	KillCounter();
	int eventHandler(const df::Event* p_e);
};