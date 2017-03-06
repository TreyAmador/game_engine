#ifndef SPRITE_H_
#define SPRITE_H_
#include <string>
#include "geometry.h"
class Graphics;
struct Color;


class Sprite {

public:
	Sprite();
	Sprite( 
		Graphics& graphics, 
		const std::string& filePath, 
		int sourceFrameX, int sourceFrameY, 
		int widthPixels, int heightPixels );

	Sprite(
		Graphics& graphics,
		const std::string& filePath,
		const Color& colorKey,
		int sourceFrameX, int sourceFrameY,
		int widthPixels, int heightPixels);

	// probably don't need virtual destructor in base
	virtual ~Sprite();

	virtual void update(int elapsedTime);
	void draw(Graphics& graphics, int x, int y);

protected:
	SDL_Texture* sprite_sheet_;
	Rectangle source_rectangle_;

};

#endif
