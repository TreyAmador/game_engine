#ifndef SINGLE_RECTANGLE_H_
#define SINGLE_RECTANGLE_H_
#include "body.h"


class SingleRectangle : public Body {

public:
	SingleRectangle();
	SingleRectangle(const Point2D& pos);
	virtual ~SingleRectangle();

	virtual void tile_collisions(WorldMap& map, const Point2D& delta);
	
	virtual void react_top_collision() = 0;
	virtual void react_bottom_collision() = 0;
	virtual void react_right_collision() = 0;
	virtual void react_left_collision() = 0;

	Rectangle collision_rectangle();

	virtual bool on_ground() = 0;
	virtual void update(int elapsedTime) = 0;
	virtual void draw(Graphics& graphics, int x, int y) = 0;

protected:
	Rectangle collision_;

};

#endif
