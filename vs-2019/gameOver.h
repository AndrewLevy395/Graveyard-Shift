#include "ViewObject.h"
#include "Object.h"

class GameOver : public df::ViewObject {
	public:
		GameOver();
		~GameOver();
		int draw();
	private:
		int time_to_live;
		int eventHandler(const df::Event* p_e);
		void step();

};
