#ifndef GLOBALS_H_
#define GLOBALS_H_


namespace global {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
}


enum GameState {
	PLAY,
	QUIT,
	PAUSE,
	MENU
};

extern GameState game_state_;


struct Color {
	int r, g, b;
	Color(int r, int g, int b) : 
		r(r), g(g), b(b) 
	{}
};


#endif