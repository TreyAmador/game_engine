#include "fountain.h"
#include "graphics.h"
#include "camera.h"


namespace {
	const int TOTAL_LIFESPAN_MS = 1000;
	const float GRAVITY_ACCELERATION = 0.0024f;

	const float VEL_X = 1.2f;
	const float VEL_Y = 0.8f;	// make negative

	const float PERCENT = 100.0f;
}


Fountain::Fountain() {}


Fountain::Fountain(
	std::shared_ptr<Sprite> sprite, 
	const Point2D& pos) :
	Particle(pos), sprite_(sprite), current_time_(0)
{
	velocity_.x = (VEL_X * ((rand() % 100) / PERCENT)) - (0.5f * VEL_X);
	velocity_.y = -(VEL_Y - std::fabsf(velocity_.x));
}


Fountain::~Fountain() {
	sprite_.reset();
}


bool Fountain::has_expired() {
	return current_time_ > TOTAL_LIFESPAN_MS;
}


bool Fountain::is_visible() {
	return current_time_ % 2 == 0;
}


void Fountain::shift_x(int offset) {
	position_.x += offset;
}


void Fountain::shift_y(int offset) {
	position_.y += offset;
}


void Fountain::shift_position(const Point2D& offset) {
	position_ += offset;
}


void Fountain::react_collision() {
	// remove this particle?
}


bool Fountain::on_ground() {
	return false;
}


// somehow get this into physics class
void Fountain::update(int elapsedTime) {
	current_time_ += elapsedTime;
	position_.y += static_cast<int>(
		GRAVITY_ACCELERATION * elapsedTime * elapsedTime + 
		velocity_.y * elapsedTime );
	velocity_.y += GRAVITY_ACCELERATION * elapsedTime;
	position_.x += static_cast<int>(velocity_.x * elapsedTime);
}


void Fountain::draw(Graphics& graphics, int x, int y) {
	sprite_->draw(graphics, x, y);
}


