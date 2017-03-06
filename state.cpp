#include "state.h"


State::State(
	Movement movement, Horizontality horizontal, Verticality vertical) :
	movement_(movement), horizontality_(horizontal), 
	verticality_(vertical), jump_(false, true), enter_door_(true)
{}


State::Jump::Jump(bool grounded, bool recovered) :
	grounded_(grounded), recovered_(recovered)
{}


void State::update_state(const Vector2D& velocity, const Vector2D& acceleration) {	
	if (velocity.y < 0.0f)
		movement_ = Movement::RISE;
	else if (velocity.y > 0.0f)
		movement_ = Movement::FALL;

	if (acceleration.x != 0.0f && velocity.y == 0.0f && verticality_ == Verticality::DOWN)
		verticality_ = Verticality::SIDE;
}


bool operator<(const State& lh, const State& rh) {
	if (lh.movement_ != rh.movement_)
		return lh.movement_ < rh.movement_;
	if (lh.horizontality_ != rh.horizontality_)
		return lh.horizontality_ < rh.horizontality_;
	if (lh.verticality_ != rh.verticality_)
		return lh.verticality_ < rh.verticality_;
	return false;
}


