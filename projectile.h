#ifndef PROJECTILE_H_
#define PROJECTILE_H_
#include "sprite.h"
#include "particle.h"
class Graphics;
class Camera;


// the player should have a fire which puts projectile on list
// the gun class will need to be passed a WorldMap reference?
// for the time being, the gun class will be in control of projectile sprites
// gun should also have recoil time

// note you could make the constructor accept a pointer to a sprite
// which is generated each time you fire
// each bullet would point to the same sprite
class Projectile : public Particle {

public:
	Projectile();
	Projectile(
		Point2D& position, 
		Point2D& direction);

	virtual ~Projectile();

	virtual bool has_expired();
	virtual bool is_visible();

	virtual void react_collision();

	virtual bool on_ground();

	virtual void update(int elapsedTime);
	virtual void draw(Graphics& graphics, int x, int y);

	int x();
	int y();

	float velocity_x();
	float velocity_y();

private:
	int lifespan_timer_;
	bool remove_;

};

#endif
