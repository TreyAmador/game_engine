#include <random>
#include "enemy.h"
#include "camera.h"
#include "worldmap.h"
#include "globals.h"
#include "graphics.h"


namespace {
	const std::string SPRITE_PATH = "content/MyChar.bmp";
	const float FRAME_LENGTH_MS = 80.0f;
	const int SPRITE_WIDTH_PIXELS = 32;
	const int SPRITE_HEIGHT_PIXELS = 32;

	const float VELOCITY_X = 0.5f;
	const float VELOCITY_Y = 0.5f;

	const int TIME_MOVING_MS = 500;
}


Enemy::Enemy() {

}


Enemy::Enemy(Graphics& graphics, Point2D& spawnPoint) :
	DualRectangle(spawnPoint),
	current_state_(0),
	movement_timer_(0), reaction_timer_(0),
	enemy_state_(IDLE_RIGHT)
{
	setup_animations(graphics);
}


// this may be very, very wrong....
Enemy::~Enemy() {
	for (auto iter = sprites_.begin(); iter != sprites_.end(); ++iter) {
		iter->second.reset();
	}
	sprites_.clear();
}


void Enemy::setup_animations(Graphics& graphics) {
	setup_enemy(graphics, IDLE_LEFT, 0, 12);
	setup_enemy(graphics, IDLE_RIGHT, 0, 13);
	setup_enemy(graphics, WALKING_LEFT, { 0,1,0,2 }, 12, FRAME_LENGTH_MS);
	setup_enemy(graphics, WALKING_RIGHT, { 0,1,0,2 }, 13, FRAME_LENGTH_MS);
}


void Enemy::setup_enemy(Graphics& graphics, EnemyState state, std::vector<int> xFrames, int yFrame, float frameLength) {
	sprites_[state] = std::shared_ptr<Sprite>(new AnimatedSprite(
		graphics, SPRITE_PATH, Color(0, 0, 0), xFrames, yFrame,
		SPRITE_WIDTH_PIXELS, SPRITE_HEIGHT_PIXELS, FRAME_LENGTH_MS));
}


void Enemy::setup_enemy(Graphics& graphics, EnemyState state, int xFrame, int yFrame) {
	sprites_[state] = std::shared_ptr<Sprite>(new Sprite(
		graphics, SPRITE_PATH, Color(0, 0, 0), xFrame, yFrame,
		SPRITE_WIDTH_PIXELS, SPRITE_HEIGHT_PIXELS));
}


void Enemy::move_right(int elapsedTime) {
	velocity_.x = VELOCITY_X;
}


void Enemy::move_left(int elapsedTime) {
	velocity_.x = -VELOCITY_X;
}


void Enemy::idle_left(int elapsedTime) {
	velocity_.x = 0.0f;
}


void Enemy::idle_right(int elapsedTime) {
	velocity_.x = 0.0f;
}


// excellent artificial intelligence
void Enemy::artificial_intelligence(int elapsedTime) {
	movement_timer_ += elapsedTime;
	if (movement_timer_ > TIME_MOVING_MS) {
		enemy_state_ = (EnemyState)(rand() % (int)TOTAL_ENEMY_STATES);
		movement_timer_ = 0;
	}
	switch (enemy_state_) {
	case IDLE_LEFT:
		idle_left(elapsedTime);
		break;
	case IDLE_RIGHT:
		idle_right(elapsedTime);
		break;
	case WALKING_LEFT:
		move_left(elapsedTime);
		break;
	case WALKING_RIGHT:
		move_right(elapsedTime);
		break;
	default: break;
	}
}


void Enemy::update(int elapsedTime) {
	sprites_[enemy_state_]->update(elapsedTime);
	artificial_intelligence(elapsedTime);
}


void Enemy::react_top_collision(std::unique_ptr<Tile>& tile) {
	velocity_.y = 0.0f;
}


void Enemy::react_bottom_collision(std::unique_ptr<Tile>& tile) {
	velocity_.y = 0.0f;
}


void Enemy::react_left_collision(std::unique_ptr<Tile>& tile) {
	velocity_.x *= -1;
	enemy_state_ = enemy_state_ == WALKING_RIGHT ? WALKING_LEFT : WALKING_RIGHT;
}


void Enemy::react_right_collision(std::unique_ptr<Tile>& tile) {
	velocity_.x *= -1;
	enemy_state_ = enemy_state_ == WALKING_RIGHT ? WALKING_LEFT : WALKING_RIGHT;
}


bool Enemy::on_ground() {
	return true;
}


void Enemy::draw(Graphics& graphics, int x, int y) {
	sprites_[enemy_state_]->draw(graphics, x, y);
}

