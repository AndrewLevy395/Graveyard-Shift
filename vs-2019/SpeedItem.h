//
// SpeedItem.h
//

#ifndef SPEED_ITEM_H
#define SPEED_ITEM_H

// Engine includes.
#include "EventCollision.h"
#include "Object.h"

class SpeedItem : public df::Object {

protected:
	void hit(const df::EventCollision* p_c);
	int eventHandler(const df::Event* e);

public:
	SpeedItem();
};

#endif

