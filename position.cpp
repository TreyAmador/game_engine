#include "position.h"
#include "graphics.h"


namespace {
	const int COLLISION_X_WIDTH = 20;
	const int COLLISION_X_HEIGHT = 16;
	const int COLLISION_X_OFFSET_X = 6;
	const int COLLISION_X_OFFSET_Y = 2;

	const int COLLISION_Y_WIDTH = 12;
	const int COLLISION_Y_HEIGHT = 30;
	const int COLLISION_Y_OFFSET_X = 10;
	const int COLLISION_Y_OFFSET_Y = 2;
}


Position::Position() : 
	mPosition(0,0) 
{}

Position::Position(Point2D pos) : 
	mPosition(pos) 
{
	mCollisionX = {
		mPosition.x + COLLISION_X_OFFSET_X, 
		mPosition.y + COLLISION_X_OFFSET_Y, 
		COLLISION_X_WIDTH, COLLISION_X_HEIGHT 
	};
	mCollisionY = {
		mPosition.x + COLLISION_Y_OFFSET_X,
		mPosition.y + COLLISION_Y_OFFSET_Y,
		COLLISION_Y_WIDTH, COLLISION_Y_HEIGHT
	};
}


void Position::operator+=(const Point2D& rh) {
	mPosition.x += rh.x;
	mPosition.y += rh.y;
	mCollisionX.x += rh.x;
	mCollisionX.y += rh.y;
	mCollisionY.x += rh.x;
	mCollisionY.y += rh.y;
}


// i am skeptical of this method
Position& Position::operator=(const Point2D& rh) {

	int offsetX = mCollisionX.x - rh.x;
	mPosition.x -= offsetX;
	mCollisionX.x -= offsetX;
	mCollisionY.x -= offsetX;

	int offsetY = mCollisionY.y - rh.y;
	mPosition.y -= offsetY;
	mCollisionX.y -= offsetY;
	mCollisionY.y -= offsetY;

	return *this;
}


void Position::repositionX(int x) {
	int offsetX = x - mCollisionX.x;
	mPosition.x += offsetX;
	mCollisionX.x += offsetX;
	mCollisionY.x += offsetX;
}


void Position::repositionY(int y) {
	int offsetY = y - mCollisionY.y;
	mPosition.y += offsetY;
	mCollisionX.y += offsetY;
	mCollisionY.y += offsetY;
}


// an interesting note: McKids did collision detection with
// a hexagonal geometry representing the top, bottom,
// top left, top right, bottom left, bottom right points
// on the sprite.... could consider something like that
Rectangle Position::getCollisionX() {
	return mCollisionX;
}


Rectangle Position::getCollisionY() {
	return mCollisionY;
}


Rectangle Position::topRectangle(int deltaY) {
	return {
		mCollisionY.x, 
		mCollisionY.y + deltaY,
		mCollisionY.w, 
		mCollisionY.h / 2 - deltaY
	};
}


Rectangle Position::bottomRectangle(int deltaY) {
	return {
		mCollisionY.x,
		mCollisionY.y + mCollisionY.h / 2,
		mCollisionY.w,
		mCollisionY.h / 2 + deltaY
	};
}


Rectangle Position::leftRectangle(int deltaX) {
	return {
		mCollisionX.x + deltaX,
		mCollisionX.y,
		mCollisionX.w / 2 - deltaX,
		mCollisionX.h
	};
}


Rectangle Position::rightRectangle(int deltaX) {
	return {
		mCollisionX.x + mCollisionX.w / 2,
		mCollisionX.y,
		mCollisionX.w / 2 + deltaX,
		mCollisionX.h
	};
}


Rectangle Position::topRectangle() {
	return topRectangle(0);
}


Rectangle Position::bottomRectangle() {
	return bottomRectangle(0);
}


Rectangle Position::rightRectangle() {
	return rightRectangle(0);
}


Rectangle Position::leftRectangle() {
	return leftRectangle(0);
}


const int Position::x() const {
	return mPosition.x;
}


const int Position::y() const {
	return mPosition.y;
}


void Position::drawCollisionRectangles(Graphics& graphics) {
	SDL_RenderDrawRect(graphics.getRenderer(), &mCollisionX.getSDLRectangle());
	SDL_RenderDrawRect(graphics.getRenderer(), &mCollisionY.getSDLRectangle());
}



