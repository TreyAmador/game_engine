#ifndef CAMERA_H_
#define CAMERA_H_
#include "geometry.h"
#include "graphics.h"
class Body;
class Player;
class WorldMap;


class Camera {

public:
	Camera();
	Camera(int x, int y, int w, int h);
	//Camera(Graphics& graphics, Rectangle view);

	~Camera();

	void track_subject(const WorldMap& map, Player& player);
	void center_subject(const Point2D& center);

	void capture(Graphics& graphics, Body& body);
	void capture(Graphics& graphics, WorldMap& world);

	Rectangle get_camera_view();
	const int x() const;
	const int y() const;

private:
	Rectangle view_;
	//Graphics graphics_;

};

#endif
