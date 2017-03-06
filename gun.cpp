#include "gun.h"
#include "worldmap.h"
#include "globals.h"
#include "camera.h"


namespace {
	const std::string FILE_PATH = "content/MyChar.bmp";
	const int PROJECTILE_LIFESPAN = 200;
	const int MAX_RECOIL_TIME = 100;
}


Gun::Gun() {}


Gun::Gun(Graphics& graphics) : 
	projectile_sprite_(graphics, FILE_PATH, Color(0, 0, 0), 24, 1, 16, 16),
	recoiled_(false), recoil_time_(0)
{}


Gun::~Gun() {
	gun_.clear();
	gun_.shrink_to_fit();
}


void Gun::fire(Point2D& pos, Point2D& dir) {
	if (!recoiled_) {
		gun_.emplace_back(pos, dir);
		recoiled_ = true;
	}
}


void Gun::remove() {}


// the bullet removal algorithm needs updating...
// center the collision rect on the projectile
void Gun::update(int elapsedTime, WorldMap& map) {
	auto iter = gun_.begin();
	while (iter != gun_.end()) {
		iter->update(elapsedTime);
		iter->tile_collisions(map, { 0,0 });
		if (iter->has_expired()) {
			iter = gun_.erase(iter);
		}
		else {
			++iter;
		}
	}
	if (recoiled_) {
		recoil_time_ += elapsedTime;
		if (recoil_time_ > MAX_RECOIL_TIME) {
			recoil_time_ = 0;
			recoiled_ = false;
		}
	}
}


void Gun::draw(Graphics& graphics) {
	for (size_t i = 0; i < gun_.size(); ++i) {
		projectile_sprite_.draw(graphics, gun_[i].x(), gun_[i].y());
	}
}


void Gun::draw(Graphics& graphics, Camera& camera) {
	for (size_t i = 0; i < gun_.size(); ++i) {
		projectile_sprite_.draw(graphics, gun_[i].x() - camera.x(), gun_[i].y() - camera.y());
	}
}
