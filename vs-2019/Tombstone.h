//
// Tombstone.h
//

#ifndef TOMBSTONE_H
#define TOMBSTONE_H

#include "Object.h"
#include "LogManager.h"
#include "EventCollision.h"


class Tombstone : public df::Object {

private: 

	int hit(const df::EventCollision* p_c);

public:

	// Construct wall with give (x,y) size.
	Tombstone();

	int eventHandler(const df::Event* e);
};

#endif

