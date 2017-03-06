#pragma once
#include "physics.h"
#include "worldmap.h"
#include "particleengine.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"


class World {


private:
	Physics mPhysics;
	WorldMap mMap;
	ParticleEngine mParticleEngine;
	Camera mCamera;
	Player mPlayer;
	Enemy mEnemy;


public:
	void update(int elapsedTime);
	void draw(Graphics& graphics);




};