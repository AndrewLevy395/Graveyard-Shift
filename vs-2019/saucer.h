#include "Object.h"
#include "EventCollision.h"
#include "hero.h"

class Saucer : public df::Object {
private:
	void moveToStart();
	void out();
	void hit(const df::EventCollision* p_c);
	int isTanker;
	Hero* p_hero;


public:
	Saucer();
	~Saucer();
	int eventHandler(const df::Event* p_e);
};