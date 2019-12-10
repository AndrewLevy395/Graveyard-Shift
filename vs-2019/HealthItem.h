//
// HealthItem.h
//

#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

// Engine includes.
#include "EventCollision.h"
#include "Object.h"

class HealthItem : public df::Object {

protected:
	void hit(const df::EventCollision* p_c);
	int eventHandler(const df::Event* e);

public:
	HealthItem();
};

#endif

