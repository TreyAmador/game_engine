#include "tile.h"
#include "graphics.h"
#include "sprite.h"
#include "camera.h"
#include "globals.h"


namespace {
	const float FRICTION_CONSTANT = 0.8f;
}


Tile::Tile() {}


Tile::Tile(
	Graphics& graphics, const std::string& filepath,
	int sourceFrameX, int sourceFrameY,
	int widthPixels, int heightPixels, 
	int xPos, int yPos, bool collidable) : 
	collidable_(collidable)
{
	collision_.x = xPos;
	collision_.y = yPos;
	collision_.w = widthPixels;
	collision_.h = heightPixels;

	tile_sprite_ = std::make_shared<Sprite>(
		graphics, filepath, Color(0, 0, 0),
		sourceFrameX, sourceFrameY,
		widthPixels, heightPixels);

}


Tile::Tile(
	std::shared_ptr<Sprite> sprite, 
	int xPos, int yPos, 
	int width, int height, 
	bool collidable) : 
	tile_sprite_(sprite),
	collidable_(collidable)
{
	collision_.x = xPos;
	collision_.y = yPos;
	collision_.w = width;
	collision_.h = height;
}


Tile::~Tile() {
	tile_sprite_.reset();
}


void Tile::react_top_collision() {}


void Tile::react_bottom_collision() {}


void Tile::react_right_collision() {}


void Tile::react_left_collision() {}


bool Tile::on_ground() {
	return true;
}


void Tile::update(int elapsedTime) {
	// TODO: perhaps have animated tiles?
}


void Tile::draw(Graphics& graphics, int x, int y) {
	tile_sprite_->draw(graphics, x, y);
}


const float Tile::friction() const {
	return FRICTION_CONSTANT;
}


const int Tile::x() const {
	return collision_.x;
}


const int Tile::y() const {
	return collision_.y;
}


const int Tile::w() const {
	return collision_.w;
}

const int Tile::h() const {
	return collision_.h;
}


bool Tile::is_collidable() {
	return collidable_;
}

