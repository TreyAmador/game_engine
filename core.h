#ifndef CORE_H_
#define CORE_H_
#include "player.h"
#include "globals.h"
#include "worldmap.h"
#include "camera.h"
#include "particleengine.h"
#include "enemy.h"
class Graphics;





class Core {

public:
	Core();
	~Core();

	void main_loop();
	void pause_game();
	void draw(Graphics& graphics);
	void update(int elapsedTime);



private:
	Player player_;
	WorldMap world_;
	Camera camera_;
	Enemy enemy_;
	ParticleEngine particle_engine_;

};

#endif
