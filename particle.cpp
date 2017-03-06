#include <memory>
#include "particle.h"
#include "worldmap.h"


Particle::Particle() : 
	Body({0,0}, {0,0}, {0,0}) 
{}


Particle::Particle(const Point2D& pos) :
	Body(pos, {0,0}, {0,0})
{}


Particle::~Particle() {}


void Particle::tile_collisions(WorldMap& map, const Point2D& delta) {
	// could use a much lighter algorithm
	// ie collidesWith in the rect algorithm which can be implemented in map
	position_ += delta;
	std::unique_ptr<Tile> collisionRect = map.collisionsAABB(Rectangle(position_));
	if (collisionRect != nullptr) {
		react_collision();
	}
}

