#include <memory>
#include "dualrectangle.h"
#include "graphics.h"
#include "worldmap.h"


// these should be passed-in offsets from player / enemy
namespace {
	const int COLLISION_X_WIDTH = 20;
	const int COLLISION_X_HEIGHT = 16;
	const int COLLISION_X_OFFSET_X = 6;
	const int COLLISION_X_OFFSET_Y = 2;

	const int COLLISION_Y_WIDTH = 12;
	const int COLLISION_Y_HEIGHT = 30;
	const int COLLISION_Y_OFFSET_X = 10;
	const int COLLISION_Y_OFFSET_Y = 2;
}


DualRectangle::DualRectangle() :
	Body({0,0}, {0,0}, {0,0})
{}


DualRectangle::DualRectangle(const Point2D& pos) :
	Body(pos, {0,0}, {0,0})
{
	collision_x_ = {
		position_.x + COLLISION_X_OFFSET_X,
		position_.y + COLLISION_X_OFFSET_Y,
		COLLISION_X_WIDTH, COLLISION_X_HEIGHT
	};
	collision_y_ = {
		position_.x + COLLISION_Y_OFFSET_X,
		position_.y + COLLISION_Y_OFFSET_Y,
		COLLISION_Y_WIDTH, COLLISION_Y_HEIGHT
	};
}


DualRectangle::~DualRectangle() {}


void DualRectangle::operator+=(const Point2D& rh) {
	position_.x += rh.x;
	position_.y += rh.y;
	collision_x_.x += rh.x;
	collision_x_.y += rh.y;
	collision_y_.x += rh.x;
	collision_y_.y += rh.y;
}


// i am skeptical of this method
DualRectangle& DualRectangle::operator=(const Point2D& rh) {

	int offsetX = collision_x_.x - rh.x;
	position_.x -= offsetX;
	collision_x_.x -= offsetX;
	collision_y_.x -= offsetX;

	int offsetY = collision_y_.y - rh.y;
	position_.y -= offsetY;
	collision_x_.y -= offsetY;
	collision_y_.y -= offsetY;

	return *this;
}


void DualRectangle::tile_collisions(WorldMap& map, const Point2D& delta) {
	collision_x_axis(map, delta.x);
	collision_y_axis(map, delta.y);
}


void DualRectangle::collision_x_axis(WorldMap& map, int delta) {

	if (delta > 0) {
		std::unique_ptr<Tile> rightCollisions = map.collisionsAABB(right_rectangle(delta));
		if (rightCollisions != nullptr) {
			reposition_x(rightCollisions->collision_rectangle().left() - collision_x_.width());
			react_right_collision(rightCollisions);
		}
		else {
			move_x(delta);
		}
		std::unique_ptr<Tile> leftCollisions = map.collisionsAABB(left_rectangle());
		if (leftCollisions != nullptr) {
			reposition_x(leftCollisions->collision_rectangle().right());
			react_left_collision(leftCollisions);
		}
	}
	else {
		std::unique_ptr<Tile> leftCollisions = map.collisionsAABB(left_rectangle(delta));
		if (leftCollisions != nullptr) {
			reposition_x(leftCollisions->collision_rectangle().right());
			react_left_collision(leftCollisions);
		}
		else {
			move_x(delta);
		}
		std::unique_ptr<Tile> rightCollisions = map.collisionsAABB(right_rectangle());
		if (rightCollisions != nullptr) {
			reposition_x(rightCollisions->collision_rectangle().left() - collision_x_.width());
			react_right_collision(rightCollisions);
		}
	}
}

// there's a problem with this method .......
void DualRectangle::collision_y_axis(WorldMap& map, int delta) {

	if (delta > 0) {
		std::unique_ptr<Tile> bottomCollisions = map.collisionsAABB(bottom_rectangle(delta));
		if (bottomCollisions != nullptr) {
			reposition_y(bottomCollisions->collision_rectangle().top() - collision_y_.height());
			react_bottom_collision(bottomCollisions);
		}
		else {
			move_y(delta);
		}
		std::unique_ptr<Tile> topCollisions = map.collisionsAABB(top_rectangle());
		if (topCollisions != nullptr) {
			reposition_y(topCollisions->collision_rectangle().bottom());
			react_top_collision(topCollisions);
		}
	}
	else {
		std::unique_ptr<Tile> topCollisions = map.collisionsAABB(top_rectangle(delta));
		if (topCollisions != nullptr) {
			reposition_y(topCollisions->collision_rectangle().bottom());
			react_top_collision(topCollisions);
		}
		else {
			move_y(delta);
		}
		std::unique_ptr<Tile> bottomCollisions = map.collisionsAABB(bottom_rectangle());
		if (bottomCollisions != nullptr) {
			reposition_y(bottomCollisions->collision_rectangle().top() - collision_y_.height());
			react_bottom_collision(bottomCollisions);
		}
	}
}


void DualRectangle::reposition_x(int x) {
	int offsetX = x - collision_x_.x;
	position_.x += offsetX;
	collision_x_.x += offsetX;
	collision_y_.x += offsetX;
}


void DualRectangle::reposition_y(int y) {
	int offsetY = y - collision_y_.y;
	position_.y += offsetY;
	collision_x_.y += offsetY;
	collision_y_.y += offsetY;
}


void DualRectangle::move_x(int x) {
	position_.x += x;
	collision_x_.x += x;
	collision_y_.x += x;
}


void DualRectangle::move_y(int y) {
	position_.y += y;
	collision_x_.y += y;
	collision_y_.y += y;
}


void DualRectangle::set_x(int x) {

}


void DualRectangle::set_y(int y) {

}


Rectangle DualRectangle::top_rectangle(int deltaY) {
	return{
		collision_y_.x,
		collision_y_.y + deltaY,
		collision_y_.w,
		collision_y_.h / 2 - deltaY
	};
}


Rectangle DualRectangle::bottom_rectangle(int deltaY) {
	return{
		collision_y_.x,
		collision_y_.y + collision_y_.h / 2,
		collision_y_.w,
		collision_y_.h / 2 + deltaY
	};
}


Rectangle DualRectangle::left_rectangle(int deltaX) {
	return{
		collision_x_.x + deltaX,
		collision_x_.y,
		collision_x_.w / 2 - deltaX,
		collision_x_.h
	};
}


Rectangle DualRectangle::right_rectangle(int deltaX) {
	return{
		collision_x_.x + collision_x_.w / 2,
		collision_x_.y,
		collision_x_.w / 2 + deltaX,
		collision_x_.h
	};
}


Rectangle DualRectangle::top_rectangle() {
	return top_rectangle(0);
}


Rectangle DualRectangle::bottom_rectangle() {
	return bottom_rectangle(0);
}


Rectangle DualRectangle::right_rectangle() {
	return right_rectangle(0);
}


Rectangle DualRectangle::left_rectangle() {
	return left_rectangle(0);
}


Rectangle DualRectangle::collision_x() {
	return collision_x_;
}


Rectangle DualRectangle::collision_y() {
	return collision_y_;
}


const int DualRectangle::x() const {
	return position_.x;
}


const int DualRectangle::y() const {
	return position_.y;
}


void DualRectangle::draw_collision_rectangles(Graphics& graphics) {
	SDL_RenderDrawRect(graphics.get_renderer(), &collision_x_.SDL_Rectangle());
	SDL_RenderDrawRect(graphics.get_renderer(), &collision_y_.SDL_Rectangle());
}

