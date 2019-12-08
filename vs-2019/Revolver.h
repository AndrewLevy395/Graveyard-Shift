
#ifndef REVOLVER_H
#define REVOLVER_H

// Engine includes.
#include "EventCollision.h"
#include "Object.h"

class Revolver : public df::Object {

protected:
	void hit(const df::EventCollision* p_c);
	int eventHandler(const df::Event* e);

public:
	Revolver();
};

#endif

