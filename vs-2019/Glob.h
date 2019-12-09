#include "Object.h"
#include "EventCollision.h"
#include "hero.h"

class Glob : public df::Object {

private:
	void out();
	void hit(const df::EventCollision* p_collision_event);

public:
	Glob();
	int eventHandler(const df::Event* p_e);
};