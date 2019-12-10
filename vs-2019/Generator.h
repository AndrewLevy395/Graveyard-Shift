
#ifndef GEN_H
#define GEN_H

// Engine includes.
#include "Object.h"

class Generator : public df::Object {
private:
	bool on;
public:
	Generator(df::Vector position);
	int eventHandler(const df::Event* e);
	void stopAnimation(bool stop);
};

#endif

