#pragma once
#include "geometry.h"
class Graphics;


// you could potentially have various physical attributes of all bodies
// ex Force vectors, velocity, position, etc...
// all would be components of Body superclass inhereted by subclasses
class Position {

private:
	Point2D mPosition;

	// revise the class to include any number of collision rectangles
	Rectangle mCollisionX, mCollisionY;

public:
	Position();
	Position(Point2D pos);

	void operator+=(const Point2D& rh);
	Position& operator=(const Point2D& rh);

	void repositionX(int x);
	void repositionY(int y);

	Rectangle getCollisionX();
	Rectangle getCollisionY();

	Rectangle topRectangle(int deltaY);
	Rectangle bottomRectangle(int deltaY);
	Rectangle leftRectangle(int deltaX);
	Rectangle rightRectangle(int deltaX);

	// these are probably less efficient than need be
	// considering they simply call the other collision functions
	// that is too many returns / calls
	// consider revising to shave time
	Rectangle topRectangle();
	Rectangle bottomRectangle();
	Rectangle leftRectangle();
	Rectangle rightRectangle();

	const int x() const;
	const int y() const;

	void drawCollisionRectangles(Graphics& graphics);

	// any position setter will need to also modify the collision rectangles

	// you may consider making a function which accepts rectangles represeting tiles
	// and uses the preexisting collision rectangles in position for collision detection
	// as opposed to returning new rectangles
};


