#ifndef NONPHYSICAL_H_
#define NONPHYSICAL_H_
#include "body.h"


class NonPhysical : public Body {

public:
	NonPhysical();
	NonPhysical(const Point2D& pos, const Vector2D& vec, const Vector2D& acc);
	virtual ~NonPhysical();

	virtual void tile_collisions(WorldMap& map, const Point2D& delta);
	virtual bool on_ground() = 0;

	virtual void update(int elapsedTime) = 0;
	virtual void draw(Graphics& graphics, int x, int y) = 0;

};

#endif
