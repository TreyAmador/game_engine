#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_
#include <vector>
#include "sprite.h"


class AnimatedSprite : public Sprite {

public:
	AnimatedSprite();

	AnimatedSprite(Graphics& graphics, const std::string& filePath, 
		const std::vector<int>& framesIndeces, int sourceFrameY, 
		int width, int height, float frameTime);

	AnimatedSprite(Graphics& graphics, const std::string& filePath,
		const Color& colorKey,
		const std::vector<int>& framesIndeces, int sourceFrameY,
		int width, int height, float frameTime);

	virtual ~AnimatedSprite();

	void update(int elapsedTime);

private:
	std::vector<Rectangle> animation_;
	int current_frame_, total_frames_;
	float total_frame_time_, current_frame_time_;

};

#endif
