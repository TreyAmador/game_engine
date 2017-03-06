#include "body.h"


Body::Body(const Point2D& pos, const Vector2D& vel, const Vector2D& acc) :
	position_(pos), velocity_(vel), acceleration_(acc)
{}


Body::~Body() {}


void Body::shift_pos_x(int x) {
	position_.x += x;
}


void Body::shift_pos_y(int y) {
	position_.y += y;
}


void Body::shift_vel_x(float x) {
	velocity_.x += x;
}


void Body::shift_vel_y(float y) {
	velocity_.y += y;
}


void Body::shift_acc_x(float x) {
	acceleration_.x += x;
}


void Body::shift_acc_y(float y) {
	acceleration_.y += y;
}


void Body::set_pos_x(int x) {
	position_.x = x;
}

void Body::set_pos_y(int y) {
	position_.y = y;
}


void Body::set_vel_x(float x) {
	velocity_.x = x;
}


void Body::set_vel_y(float y) {
	velocity_.y = y;
}


void Body::set_acc_x(float x) {
	acceleration_.x = x;
}


void Body::set_acc_y(float y) {
	acceleration_.y = y;
}


Point2D Body::position() {
	return position_;
}


Vector2D Body::velocity() {
	return velocity_;
}


Vector2D Body::acceleration() {
	return acceleration_;
}


