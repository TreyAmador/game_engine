#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "globals.h"


Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(global::SCREEN_WIDTH, global::SCREEN_HEIGHT, 0, &window_, &renderer_);
	SDL_SetWindowTitle(window_, "Engine Test");
}


Graphics::~Graphics() {
	for (auto iter = sprite_sheets_.begin(); iter != sprite_sheets_.end(); ++iter)
		SDL_FreeSurface(iter->second);
	sprite_sheets_.clear();
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}


SDL_Surface* Graphics::load_image(const std::string& filepath, const Color& color) {
	if (sprite_sheets_.count(filepath) == 0) {
		sprite_sheets_[filepath] = IMG_Load(filepath.c_str());
		SDL_SetColorKey(
			sprite_sheets_[filepath], SDL_TRUE,
			SDL_MapRGB(sprite_sheets_[filepath]->format,
			color.r, color.g, color.b));
	}
	return sprite_sheets_[filepath];
}


SDL_Surface* Graphics::load_image( const std::string& filepath ) {
	if (sprite_sheets_.count(filepath) == 0 ) {
		sprite_sheets_[filepath] = IMG_Load(filepath.c_str());
	}
	return sprite_sheets_[filepath];
}

void Graphics::blit_surface( SDL_Texture* srcTxtr, SDL_Rect* srcRect, SDL_Rect* destRect ) {
	SDL_RenderCopy(renderer_, srcTxtr, srcRect, destRect);
}

void Graphics::flip() {
	SDL_RenderPresent(renderer_);
}

void Graphics::clear() {
	SDL_RenderClear(renderer_);
}

SDL_Renderer* Graphics::get_renderer() const {
	return renderer_;
}

