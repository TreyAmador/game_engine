#ifndef ENEMY_H_
#define ENEMY_H_
#include <memory>
#include <map>
#include "animatedsprite.h"
#include "geometry.h"
#include "dualrectangle.h"
class WorldMap;
class Camera;


enum EnemyState {
	IDLE_RIGHT,
	IDLE_LEFT,
	WALKING_RIGHT,
	WALKING_LEFT,
	TOTAL_ENEMY_STATES
};

class Enemy : public DualRectangle {

public:
	Enemy();
	Enemy(Graphics& graphics, Point2D& spawnPoint);

	virtual ~Enemy();

	void setup_animations(Graphics& graphics);

	void setup_enemy(
		Graphics& graphics, EnemyState state, 
		std::vector<int> xFrames, int yFrame, 
		float frameLength);

	void setup_enemy(
		Graphics& graphics, EnemyState state, 
		int xFrame, int yFrame);
	
	void move_left(int elapsedTime);
	void move_right(int elapsedTime);
	void idle_left(int elapsedTime);
	void idle_right(int elapsedTime);

	void artificial_intelligence(int elapsedTime);

	virtual void react_top_collision(std::unique_ptr<Tile>& tile);
	virtual void react_bottom_collision(std::unique_ptr<Tile>& tile);
	virtual void react_left_collision(std::unique_ptr<Tile>& tile);
	virtual void react_right_collision(std::unique_ptr<Tile>& tile);

	virtual bool on_ground();

	virtual void update(int elapsedTime);
	virtual void draw(Graphics& graphics, int x, int y);

private:
	int movement_timer_, reaction_timer_, current_state_;
	std::map<EnemyState, std::shared_ptr<Sprite> > sprites_;
	EnemyState enemy_state_;
	
};

#endif
