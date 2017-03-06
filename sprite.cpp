#include "sprite.h"
#include "graphics.h"
#include "globals.h"


Sprite::Sprite() {}


Sprite::Sprite( 
	Graphics& graphics, const std::string& filePath,
	int sourceFrameX, int sourceFrameY, int widthPixels, int heightPixels ) 
{
	source_rectangle_.x = sourceFrameX * widthPixels;
	source_rectangle_.y = sourceFrameY * heightPixels;
	source_rectangle_.w = widthPixels;
	source_rectangle_.h = heightPixels;

	sprite_sheet_ = SDL_CreateTextureFromSurface(graphics.get_renderer(), graphics.load_image(filePath));
	if (sprite_sheet_ == NULL) {
		printf("Error, could not load image...");
	}
}


Sprite::Sprite(
	Graphics& graphics, const std::string& filePath, const Color& colorKey,
	int sourceFrameX, int sourceFrameY, int widthPixels, int heightPixels)
{
	source_rectangle_.x = sourceFrameX * widthPixels;
	source_rectangle_.y = sourceFrameY * heightPixels;
	source_rectangle_.w = widthPixels;
	source_rectangle_.h = heightPixels;

	sprite_sheet_ = SDL_CreateTextureFromSurface(
		graphics.get_renderer(),
		graphics.load_image(filePath, colorKey));
	if (sprite_sheet_ == NULL) {
		printf("Error, could not load image...");
	}
}


Sprite::~Sprite() {
	SDL_DestroyTexture(sprite_sheet_);
}


void Sprite::update(int elapsedTime) {
	// TODO: something
}


void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect destRect = { x, y, source_rectangle_.w, source_rectangle_.h };
	graphics.blit_surface(
		sprite_sheet_,
		&source_rectangle_.SDL_Rectangle(),
		&destRect);
}

