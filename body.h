#ifndef BODY_H_
#define BODY_H_
#include "geometry.h"
class Graphics;
class WorldMap;


class Body {

public:
	Body(const Point2D& pos, const Vector2D& vel, const Vector2D& acc);
	virtual ~Body();

	virtual void tile_collisions(WorldMap& map, const Point2D& delta) = 0;

	void shift_pos_x(int x);
	void shift_pos_y(int y);
	void shift_vel_x(float x);
	void shift_vel_y(float y);
	void shift_acc_x(float x);
	void shift_acc_y(float y);

	void set_pos_x(int x);
	void set_pos_y(int y);
	void set_vel_x(float x);
	void set_vel_y(float y);
	void set_acc_x(float x);
	void set_acc_y(float y);

	Point2D position();
	Vector2D velocity();
	Vector2D acceleration();

	virtual bool on_ground() = 0;

	virtual void update(int elapsedTime) = 0;
	virtual void draw(Graphics& graphics, int x, int y) = 0;

protected:
	Point2D position_;
	Vector2D velocity_;
	Vector2D acceleration_;

};

#endif
