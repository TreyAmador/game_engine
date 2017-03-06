#include "ethereal.h"
#include "graphics.h"
#include "camera.h"


namespace {
	const int TOTAL_LIFESPAN_MS = 1000;
	const int PARTICLE_DISTANCE = 64;
}


Ethereal::Ethereal() {}


Ethereal::Ethereal(
	std::shared_ptr<Sprite> sprite,
	const Point2D& pos) :
	Particle(pos), 
	sprite_(sprite), current_time_(0)
{
	position_.x += (rand() % PARTICLE_DISTANCE) - (PARTICLE_DISTANCE / 2);
	position_.y += (rand() % PARTICLE_DISTANCE) - (PARTICLE_DISTANCE / 2);
	velocity_ = { 0.0f, 0.0f };
}


Ethereal::~Ethereal() {
	sprite_.reset();
}


bool Ethereal::has_expired() {
	return current_time_ > TOTAL_LIFESPAN_MS;
}


bool Ethereal::is_visible() {
	return current_time_ % 3 == 0;
}


void Ethereal::react_collision() {

}


bool Ethereal::on_ground() {
	return false;
}


void Ethereal::update(int elapsedTime) {
	current_time_ += elapsedTime;
}


// this needs to be handled sumhow
void Ethereal::draw(Graphics& graphics, int x, int y) {
	sprite_->draw(graphics, x, y);
}

