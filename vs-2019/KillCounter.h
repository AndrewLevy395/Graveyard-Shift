#include "Object.h"
#include "ViewObject.h"
#include "Event.h"

#define KILLCOUNT_STRING "KILLS:"

class KillCounter : public df::ViewObject {

private:
	bool bossStatus;

public:
	KillCounter();
	int eventHandler(const df::Event* p_e);
};