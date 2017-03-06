#ifndef GUN_H_
#define GUN_H_
#include <vector>
#include "sprite.h"
#include "projectile.h"
class WorldMap;
class Camera;


class Gun {

public:
	Gun();
	Gun(Graphics& graphics);

	~Gun();

	void fire(Point2D& pos, Point2D& dir);

	void remove();
	void update(int elapsedTime, WorldMap& map);

	void draw(Graphics& graphics);
	void draw(Graphics& graphics, Camera& camera);

private:
	std::vector<Projectile> gun_;
	Sprite projectile_sprite_;
	bool recoiled_;
	int recoil_time_;

};

#endif
