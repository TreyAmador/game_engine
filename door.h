#ifndef DOOR_H_
#define DOOR_H_
#include <string>
#include "geometry.h"
class WorldMap;
class Graphics;


class Door {

public:
	Door();
	Door(
		const std::string& destination, 
		const Point2D& spawn, 
		int x, int y, int w, int h);

	~Door();

	bool in_threshold(const Rectangle& collision);
	void enter(Graphics& graphics, WorldMap& map);

	std::string destination();

	Point2D spawn_point();

private:
	Rectangle door_;
	std::string destination_;
	Point2D spawn_point_;

};


#endif
