#ifndef FOUNTAIN_H_
#define FOUNTAIN_H_
#include <memory>
#include <string>
#include "particle.h"
#include "sprite.h"
class Graphics;
class Camera;


class Fountain : public Particle {

public:
	Fountain();
	Fountain(
		std::shared_ptr<Sprite> sprite, 
		const Point2D& pos);
	
	virtual ~Fountain();

	void shift_x(int offset);
	void shift_y(int offset);
	void shift_position(const Point2D& offset);

	virtual void react_collision();

	virtual bool has_expired();
	virtual bool is_visible();
	virtual bool on_ground();

	virtual void update(int elapsedTime);
	virtual void draw(Graphics& graphics, int x, int y);

private:
	std::shared_ptr<Sprite> sprite_;
	int current_time_;

};

#endif
