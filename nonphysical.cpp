#include "nonphysical.h"


NonPhysical::NonPhysical() :
	Body({0,0}, {0,0}, {0,0})
{}


NonPhysical::NonPhysical(
	const Point2D& pos,
	const Vector2D& vec,
	const Vector2D& acc) :
	Body(pos,vec,acc)
{}


NonPhysical::~NonPhysical() {}


void NonPhysical::tile_collisions(WorldMap& map, const Point2D& delta) {}





