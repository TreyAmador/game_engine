#ifndef ETHEREAL_H_
#define ETHEREAL_H_
#include <memory>
#include <string>
#include "particle.h"
#include "sprite.h"


class Ethereal : public Particle {

public:
	Ethereal();
	Ethereal(
		std::shared_ptr<Sprite> sprite, 
		const Point2D& pos);

	virtual ~Ethereal();

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
