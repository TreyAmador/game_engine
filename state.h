#ifndef STATE_H_
#define STATE_H_
#include "geometry.h"


struct State {

public:
	enum Movement {
		IDLE,
		WALK,
		RISE,
		FALL
	};

	enum Horizontality {
		LEFT,
		RIGHT
	};

	enum Verticality {
		UP,
		SIDE,
		DOWN
	};

	struct Jump {
		Jump(bool grounded, bool recovered);
		bool grounded_, recovered_;
	};

	State(
		Movement movement = Movement::IDLE, 
		Horizontality horizontal = Horizontality::RIGHT, 
		Verticality vertical = Verticality::SIDE);

	void update_state(const Vector2D& velocity, const Vector2D& acceleration);
	friend bool operator<(const State& lh, const State& rh);

	Movement movement_;
	Horizontality horizontality_;
	Verticality verticality_;
	Jump jump_;
	bool enter_door_;

};

#endif
