#ifndef TILE_H_
#define TILE_H_
#include <memory>
#include <string>
#include "singlerectangle.h"
#include "geometry.h"
class Sprite;
class Camera;


// note that the map itself could draw the sprites
// ie a pointer to a sprite is initialized
// and the sprite of each tile is set equal to it
// an animated tile could inherit form tile
// and reference tile's draw function
// but would have an update which moves the source rect over
class Tile : public SingleRectangle {

public:
	Tile();
	Tile(
		Graphics& graphics,
		const std::string& filepath,
		int sourceFrameX, int sourceFrameY,
		int widthPixels, int heightPixels, 
		int xPos, int yPos,
		bool collidable = true);
	Tile(
		std::shared_ptr<Sprite> sprite, 
		int xPos, int yPos, 
		int width, int height,
		bool collidable = true);

	virtual ~Tile();

	virtual void react_top_collision();
	virtual void react_bottom_collision();
	virtual void react_right_collision();
	virtual void react_left_collision();
	virtual bool on_ground();

	void update(int elapsedTime);
	void draw(Graphics& graphics, int x, int y);

	const float friction() const;
	bool is_collidable();
	const int x() const;
	const int y() const;
	const int w() const;
	const int h() const;

private:
	std::shared_ptr<Sprite> tile_sprite_;
	bool collidable_;

};

#endif
