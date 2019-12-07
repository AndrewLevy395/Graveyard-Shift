//
// Wall.h
//

// Engine includes.
#include "DisplayManager.h"
#include "LogManager.h"

// Game includes.
#include "Wall.h"

Wall::Wall(int width, int height) {

	// Basic Wall attributes.
	setType("Wall");
	setSolidness(df::HARD);

	// Set width and height.
	m_width = width;
	m_height = height;

	// Create bounding box.
	df::Vector corner(-1 * m_width / 2.0f, -1 * m_height / 2.0f);
	df::Box box(corner, (float)m_width, (float)m_height);
	setBox(box);
}

// Draw Wall centered at position.
int Wall::draw() {

	df::Vector pos = getPosition();
	for (int y = -1 * m_height / 2; y <= m_height / 2; y++)
		for (int x = -1 * m_width / 2; x <= m_width / 2; x++) {
			pos.setX(getPosition().getX() + x);
			pos.setY(getPosition().getY() + y);
			DM.drawCh(pos, WALL_CHAR, WALL_COLOR);
		}

	return 0;
}
