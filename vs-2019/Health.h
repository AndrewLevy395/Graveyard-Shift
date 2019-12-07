//
// Health.h
// 

#include "Event.h"
#include "ViewObject.h"

#define HEALTH_STRING "Health"

class Health : public df::ViewObject {

public:
	Health();
	int eventHandler(const df::Event* p_e);
};

