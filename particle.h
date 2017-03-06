#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "body.h"
class Graphics;
class Camera;


class Particle : public Body {

public:
	Particle();
	Particle(const Point2D& pos);

	virtual ~Particle();

	virtual void tile_collisions(WorldMap& map, const Point2D& delta);
	virtual void react_collision() = 0;

	virtual bool has_expired() = 0;
	virtual bool is_visible() = 0;
	virtual bool on_ground() = 0;

	virtual void update(int elapsedTime) = 0;
	virtual void draw(Graphics& graphics, int x, int y) = 0;

};

#endif
