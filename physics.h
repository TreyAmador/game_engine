#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "geometry.h"
class Body;
class Position;
class WorldMap;


class Physics {

public:
	Point2D kinematics(Body& body, int elapsedTime);

};

#endif
