//
// Tombstone.h
//

#ifndef LARGE_TOMBSTONE_H
#define LARGE_TOMBSTONE_H

#include "Object.h"
#include "LogManager.h"
#include "EventCollision.h"


class LargeTombstone : public df::Object {

private:

	void determinePosition();
	int hit(const df::EventCollision* p_c);

public:

	// Construct wall with give (x,y) size.
	LargeTombstone();

	int eventHandler(const df::Event* e);
};

#endif

