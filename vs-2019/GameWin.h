#include "ViewObject.h"
#include "Object.h"

class GameWin : public df::ViewObject {
public:
	GameWin();
	~GameWin();
	int draw();
private:
	int time_to_live;
	int eventHandler(const df::Event* p_e);
	void step();

};
