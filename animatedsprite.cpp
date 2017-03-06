#include "animatedsprite.h"
#include "globals.h"


AnimatedSprite::AnimatedSprite() {}


AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& filePath, 
	const std::vector<int>& frameIndeces, int sourceFrameY, int width, int height, 
	float frameTime) : 
	Sprite(graphics, filePath, frameIndeces[0], sourceFrameY, width, height),
	current_frame_(0), total_frames_(frameIndeces.size()), 
	total_frame_time_(frameTime), current_frame_time_(0.0f)
{
	for (int i = 0; i < total_frames_; ++i) {
		animation_.emplace_back(frameIndeces[i] * width, sourceFrameY * height, width, height);
	}
}


AnimatedSprite::AnimatedSprite(
	Graphics& graphics, const std::string& filePath, const Color& colorKey,
	const std::vector<int>& frameIndeces, int sourceFrameY, int width, int height,
	float frameTime) :
	Sprite(graphics, filePath, colorKey, frameIndeces[0], sourceFrameY, width, height),
	current_frame_(0), total_frames_(frameIndeces.size()),
	total_frame_time_(frameTime), current_frame_time_(0.0f)
{
	for (int i = 0; i < total_frames_; ++i) {
		animation_.emplace_back(frameIndeces[i] * width, sourceFrameY * height, width, height);
	}

}


// super edgy way of freeing memory!
AnimatedSprite::~AnimatedSprite() {
	animation_.clear();
	animation_.shrink_to_fit();
}


void AnimatedSprite::update(int elapsedTime) {
	current_frame_time_ += elapsedTime;
	if (current_frame_time_ > total_frame_time_) {
		++current_frame_;
		current_frame_time_ = 0.0f;
		if (current_frame_ >= total_frames_) {
			current_frame_ = 0;
		}
		source_rectangle_.x = animation_[current_frame_].x;
	}
}

