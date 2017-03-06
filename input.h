#ifndef INPUT_H_
#define INPUT_H_
#include <SDL.h>
#include <map>


class Input {

public:
	void begin_new_frame();
	void key_up_event(const SDL_Event& event);
	void key_down_event(const SDL_Event& event);

	bool was_key_pressed(SDL_Scancode key);
	bool was_key_released(SDL_Scancode key);
	bool is_key_held(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> held_keys_;
	std::map<SDL_Scancode, bool> pressed_keys_;
	std::map<SDL_Scancode, bool> released_keys_;

};

#endif
