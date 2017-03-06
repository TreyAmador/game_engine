#include "door.h"
#include "graphics.h"
#include "worldmap.h"


Door::Door() {}


Door::Door(
	const std::string& destination,
	const Point2D& spawn,
	int x, int y, int w, int h) :
	destination_(destination), 
	spawn_point_(spawn)
{
	door_.x = x;
	door_.y = y;
	door_.w = w;
	door_.h = h;
}


Door::~Door() {}


bool Door::in_threshold(const Rectangle& collision) {
	return door_.collidesWith(collision);
}


void Door::enter(Graphics& graphics, WorldMap& map) {
	map.load_map(graphics, destination_);
}


std::string Door::destination() {
	return destination_;
}


Point2D Door::spawn_point() {
	return spawn_point_;
}


