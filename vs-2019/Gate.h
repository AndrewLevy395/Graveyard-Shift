
#ifndef GATE_H
#define GATE_H

#include "Object.h"
#include "LogManager.h"
#include "EventCollision.h"


class Gate : public df::Object {

private:

	int hit(const df::EventCollision* p_c);

public:

	//place gate at given position
	Gate(df::Vector position);

	int eventHandler(const df::Event* e);
};

#endif

