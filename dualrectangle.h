#ifndef DUAL_RECTANGLE_H_
#define DUAL_RECTANGLE_H_
#include <memory>
#include "body.h"
class WorldMap;
class Tile;


class DualRectangle : public Body {

public:
	DualRectangle();
	DualRectangle(const Point2D& pos);
	virtual ~DualRectangle();

	void operator+=(const Point2D& rh);
	DualRectangle& operator=(const Point2D& rh);

	virtual void tile_collisions(WorldMap& map, const Point2D& delta);
	void collision_x_axis(WorldMap& map, int delta);
	void collision_y_axis(WorldMap& map, int delta);

	virtual void react_top_collision(std::unique_ptr<Tile>& tile) = 0;
	virtual void react_bottom_collision(std::unique_ptr<Tile>& tile) = 0;
	virtual void react_left_collision(std::unique_ptr<Tile>& tile) = 0;
	virtual void react_right_collision(std::unique_ptr<Tile>& tile) = 0;

	void reposition_x(int x);
	void reposition_y(int y);

	void move_x(int x);
	void move_y(int y);

	void set_x(int x);
	void set_y(int y);

	Rectangle top_rectangle(int deltaY);
	Rectangle bottom_rectangle(int deltaY);
	Rectangle left_rectangle(int deltaX);
	Rectangle right_rectangle(int deltaX);

	Rectangle top_rectangle();
	Rectangle bottom_rectangle();
	Rectangle left_rectangle();
	Rectangle right_rectangle();

	Rectangle collision_x();
	Rectangle collision_y();

	const int x() const;
	const int y() const;

	virtual bool on_ground() = 0;
	virtual void update(int elapsedTime) = 0;
	virtual void draw(Graphics& graphics, int x, int y) = 0;

	void draw_collision_rectangles(Graphics& graphics);

protected:
	Rectangle collision_x_, collision_y_;

};

#endif
