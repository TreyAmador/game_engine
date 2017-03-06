#include "projectile.h"
#include "graphics.h"
#include "globals.h"


namespace {
	const int PROJECTILE_LIFESPAN = 1000;
	const float MAX_VELOCITY = 1.0f;
}


Projectile::Projectile() {}


Projectile::Projectile(
	Point2D& position, 
	Point2D& direction) :
	Particle(position), lifespan_timer_(0), remove_(false)
{
	velocity_.x = static_cast<float>(direction.x * MAX_VELOCITY);
	velocity_.y = static_cast<float>(direction.y * MAX_VELOCITY);
}


Projectile::~Projectile() {}


bool Projectile::has_expired() {
	return remove_ || lifespan_timer_ > PROJECTILE_LIFESPAN;
}


bool Projectile::is_visible() {
	return true;
}


bool Projectile::on_ground() {
	return false;
}


void Projectile::react_collision() {
	velocity_.x = 0.0f;
	velocity_.y = 0.0f;
	remove_ = true;
}


void Projectile::update(int elapsedTime) {
	lifespan_timer_ += elapsedTime;
	position_.x += static_cast<int>(velocity_.x * elapsedTime);
	position_.y += static_cast<int>(velocity_.y * elapsedTime);
}


void Projectile::draw(Graphics& graphics, int x, int y) {

}


int Projectile::x() {
	return position_.x;
}


int Projectile::y() {
	return position_.y;
}


float Projectile::velocity_x() {
	return velocity_.x;
}


float Projectile::velocity_y() {
	return velocity_.y;
}

