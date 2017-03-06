#include "singlerectangle.h"


namespace {
	// move this into constructor
	const int COLLISION_WIDTH = 32;
	const int COLLISION_HEIGHT = 32;
}


SingleRectangle::SingleRectangle() :
	Body({0,0}, {0,0}, {0,0})
{}


SingleRectangle::SingleRectangle(const Point2D& pos) :
	Body(pos, {0,0}, {0,0})
{
	collision_.x = pos.x;
	collision_.y = pos.y;
	collision_.w = COLLISION_WIDTH;
	collision_.h = COLLISION_HEIGHT;
}


SingleRectangle::~SingleRectangle() {}


void SingleRectangle::tile_collisions(WorldMap& map, const Point2D& delta) {

}


Rectangle SingleRectangle::collision_rectangle() {
	return collision_;
}


