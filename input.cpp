#include "input.h"


void Input::begin_new_frame() {
	pressed_keys_.clear();
	released_keys_.clear();
}


void Input::key_down_event(const SDL_Event& event) {
	pressed_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = true;
}


void Input::key_up_event( const SDL_Event& event ) {
	released_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = false;
}


bool Input::was_key_pressed(SDL_Scancode key) {
	return pressed_keys_[key];
}

bool Input::was_key_released(SDL_Scancode key) {
	return released_keys_[key];
}

bool Input::is_key_held(SDL_Scancode key) {
	return held_keys_[key];
}

