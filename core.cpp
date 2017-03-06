#include <algorithm>
#include "core.h"
#include "graphics.h"
#include "input.h"


namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

GameState game_state_ = PLAY;


Core::Core() {
	SDL_Init(SDL_INIT_EVERYTHING);
}


Core::~Core() {
	SDL_Quit();
}


void Core::main_loop() {

	Graphics graphics;
	SDL_Event event;
	Input input;
	//game_state_ = PLAY;

	player_ = Player(graphics, Point2D(64,480));
	enemy_ = Enemy(graphics, Point2D(288,128));
	particle_engine_ = ParticleEngine(graphics, { "shimmer" }, PARTICLE_ETHEREAL, 10, { 320, 192 });
	world_.load_map(graphics, "map05");
	
	int lastUpdateTime = SDL_GetTicks();
	while (game_state_ != QUIT) {
		const int startTimeMS = SDL_GetTicks();
		input.begin_new_frame();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				input.key_down_event(event);
				break;
			case SDL_KEYUP:
				input.key_up_event(event);
				break;
			case SDL_QUIT:
				game_state_ = QUIT;
				break;
			default: break;
			}
		}
		if (input.was_key_pressed(SDL_SCANCODE_ESCAPE))
			game_state_ = QUIT;
		if (input.was_key_pressed(SDL_SCANCODE_RETURN))
			pause_game();

		const int currentTimeMS = SDL_GetTicks();
		world_.move_maps(graphics, player_);
		if (game_state_ != PAUSE) {
			player_.handle_input(input);
		
			update(currentTimeMS - lastUpdateTime);
		}
		lastUpdateTime = currentTimeMS;
		
		draw(graphics);
		
		const int MSperFrame = 1000 / FPS;
		const int elapsedTimeMS = SDL_GetTicks() - startTimeMS;
		if (elapsedTimeMS < MSperFrame)
			SDL_Delay(MSperFrame - elapsedTimeMS);
	}
}


void Core::pause_game() {
	if (game_state_ != PAUSE)
		game_state_ = PAUSE;
	else if (game_state_ == PAUSE)
		game_state_ = PLAY;
}


void Core::draw(Graphics& graphics) {
	graphics.clear();
	camera_.track_subject(world_, player_);
	camera_.capture(graphics, world_);	
	camera_.capture(graphics, enemy_);
	camera_.capture(graphics, player_);
	camera_.capture(graphics, particle_engine_);
	graphics.flip();
}


void Core::update(int elapsedTime) {
	world_.update(player_, elapsedTime);
	world_.update(enemy_, elapsedTime);
	world_.update(particle_engine_, elapsedTime);
}

