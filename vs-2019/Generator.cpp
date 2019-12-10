#include "Generator.h"
#include "WorldManager.h"
#include "EventCollision.h"
#include "DataManager.h"
#include "Frenzy.h"
#include "Gate.h"


Generator::Generator(df::Vector position) {
	setSolidness(df::HARD);
	setSprite("generator");
	setType("generator");
	setPosition(position);
	stopAnimation(true);
	on = false;
}

// Handle event.
// Return 0 if ignored, else 1
int Generator::eventHandler(const df::Event* e) {

	if (e->getType() == df::COLLISION_EVENT && !on) {
		const df::EventCollision* p_c = dynamic_cast <df::EventCollision const*> (e);
		if (p_c->getObject1()->getType() == "hero" || p_c->getObject2()->getType() == "hero") {
			if (DATA.getNumGas() == 3) {
				DATA.removeAll("plant");
				DATA.setOnlyGoalMessage("Escape to the Exit!");
				DATA.placeLevel2Enemies(false);
				new Frenzy();
				new Gate(df::Vector(8, WM.getBoundary().getVertical()-4));
				stopAnimation(false);
				on = true;
			}
		}

		return 1;
	}
	return 0;
}

void Generator::stopAnimation(bool stop){
	df::Animation animation = getAnimation();
	if (stop){
		if (animation.getSlowdownCount() != -1)
		{
			animation.setSlowdownCount(-1);
			animation.setIndex(0);
		}
	}
	else{
		if (animation.getSlowdownCount() == -1)
		{
			animation.setSlowdownCount(0);
			animation.setIndex(0);
		}
	}
	setAnimation(animation);
}