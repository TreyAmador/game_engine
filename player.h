#ifndef PLAYER_H_
#define PLAYER_H_
#include <map>
#include <memory>
#include "dualrectangle.h"
#include "animatedsprite.h"
#include "state.h"
class WorldMap;
class Input;
class Camera;


class Player : public DualRectangle {

public:
	Player();
	Player(Graphics& graphics, Point2D spawnPoint);

	virtual ~Player();

	void setup_animations(Graphics& graphics);

	void setup_sprite(
		Graphics& graphics, 
		State::Movement movement,
		State::Horizontality horizontal,
		State::Verticality vertical,
		std::vector<int> xFrames, int yFrame, 
		float frameLength );

	void setup_sprite(
		Graphics& graphics, 
		State::Movement movement,
		State::Horizontality horizontal,
		State::Verticality vertical,
		int xFrame, int yFrame);

	void move_left();
	void move_right();
	void stop_moving();
	void start_jump();
	void decrease_jump();

	void look_horizontal();
	void look_up();
	void look_down();

	void fire();

	void set_position(const Point2D& pos);

	void spawn_at(const Point2D& pos);

	const int get_x() const;
	const int get_y() const;

	const int center_x() const;
	const int center_y() const;
	const Point2D center_position() const;

	const int width() const;
	const int height() const;

	virtual bool on_ground();
	bool can_enter();
	void has_entered();

	void handle_input(Input& input);
	
	virtual void react_top_collision(std::unique_ptr<Tile>& tile);
	virtual void react_bottom_collision(std::unique_ptr<Tile>& tile);
	virtual void react_left_collision(std::unique_ptr<Tile>& tile);
	virtual void react_right_collision(std::unique_ptr<Tile>& tile);

	State& state();

	void update(int elapsedTime);
	void draw(Graphics& graphics, int x, int y);

private:
	std::map<State, std::shared_ptr<Sprite> > sprites_;
	State state_;

};

#endif
