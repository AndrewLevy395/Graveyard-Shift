//
// Wall.h
//

#ifndef WALL_H
#define WALL_H

// Engine includes.
#include "Object.h"

#define WALL_CHAR '#'
#define WALL_COLOR df::WHITE

class Wall : public df::Object {

private:
	int m_width, m_height;

public:

	// Construct wall with give (x,y) size.
	Wall(int width, int height);

	// Draw Wall centered at position.
	int draw();
};

#endif

