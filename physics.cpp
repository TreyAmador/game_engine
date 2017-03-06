#include <algorithm>
#include "physics.h"
#include "body.h"
#include "worldmap.h"


namespace {
	const float GRAVITY_ACCELERATION = 0.0024f;

	// add a MAX_VEL_X getter for body
	const float MAX_VELOCITY_X = 0.325f;
	const float FRICTION_CONSTANT = 0.7f;
}


// the friction shit needs to be moved to collision detection
Point2D Physics::kinematics(Body& body, int elapsedTime) {
	body.shift_vel_x(body.acceleration().x * elapsedTime);
	body.shift_vel_y(GRAVITY_ACCELERATION * elapsedTime);
	return{ 
		static_cast<int>(std::round(
			body.acceleration().x*elapsedTime*elapsedTime +
			body.velocity().x*elapsedTime)),
		static_cast<int>(std::round(
			GRAVITY_ACCELERATION * elapsedTime * elapsedTime +
			body.velocity().y * elapsedTime))
	};
}

