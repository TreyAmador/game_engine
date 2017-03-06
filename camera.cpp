#include "camera.h"
#include "body.h"
#include "sprite.h"
#include "player.h"
#include "worldmap.h"


namespace {
	const int CAMERA_WIDTH = 640;
	const int CAMERA_HEIGHT = 480;
}


Camera::Camera() {
	view_.x = 0;
	view_.y = 0;
	view_.w = CAMERA_WIDTH;
	view_.h = CAMERA_HEIGHT;
}


Camera::Camera(int x, int y, int w, int h) {
	view_.x = x;
	view_.y = y;
	view_.w = w;
	view_.h = h;
}


/*
Camera::Camera(Graphics& graphics, Rectangle view) :
	graphics_(graphics) //, view_(view)
{
	view_.x = view.x;
	view_.y = view.y;
	view_.w = view.w;
	view_.h = view.h;
}
*/


Camera::~Camera() {}


void Camera::capture(Graphics& graphics, Body& body) {
	body.draw(graphics, body.position().x - view_.x, body.position().y - view_.y);
}


void Camera::capture(Graphics& graphics, WorldMap& world) {
	world.background_sprite(graphics, world.left()-(view_.left()/2), world.top()-(view_.top()/2));
	int size = world.size();
	int iRow = view_.top() / size;
	int iCol = view_.left() / size;
	int fRow = view_.bottom() == world.bottom() ? 
		view_.bottom() / size - 1 : view_.bottom() / size;
	int fCol = view_.right() == world.right() ?
		view_.right() / size - 1 : view_.right() / size;
	for (int r = iRow; r <= fRow; ++r) {
		for (int c = iCol; c <= fCol; ++c) {
			world.tiles()[r][c].draw(
				graphics, 
				world.tiles()[r][c].x() - view_.x, 
				world.tiles()[r][c].y() - view_.y);
		}
	}
}


void Camera::track_subject(const WorldMap& map, Player& subject) {
	center_subject(subject.center_position());
	if (view_.left() < 0)
		view_.x = 0;
	if (view_.right() > map.right())
		view_.x = map.right() - view_.width();
	if (view_.top() < 0)
		view_.y = 0;
	if (view_.bottom() > map.bottom())
		view_.y = map.bottom() - view_.height();
}


void Camera::center_subject(const Point2D& point) {
	view_.x = point.x - view_.w / 2;
	view_.y = point.y - view_.h / 2;
}


Rectangle Camera::get_camera_view() {
	return view_;
}


const int Camera::x() const {
	return view_.x;
}


const int Camera::y() const {
	return view_.y;
}

