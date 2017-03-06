#include <iostream>
#include <algorithm>
#include <ctgmath>
#include "player.h"
#include "core.h"
#include "input.h"
#include "worldmap.h"
#include "globals.h"
#include "graphics.h"


namespace {

	const std::string SPRITE_PATH = "content/MyChar.bmp";
	const int SPRITE_WIDTH_PIXELS = 32;
	const int SPRITE_HEIGHT_PIXELS = 32;
	const float FRAME_LENGTH_MS = 80.0f;

	// figure out friction more!
	const float MAX_VELOCITY_X = 0.325f;
	const float WALKING_ACCELERATION_X = 0.004f;
	const float REVERSE_AIRBORNE_ACCELERATION_X = 0.002f;
	const float AIR_RESISTANCE = 0.95f;
	
	const float MAX_JUMP_VELOCITY_Y = 0.9f;
	const float MIN_JUMP_VELOCITY_Y = 0.4f;
	const float TERMINAL_VELOCITY = 2.0f;

	const int LEFT_FRAME = 0;
	const int RIGHT_FRAME = 1;

}


Player::Player() {}


Player::Player(Graphics& graphics, Point2D spawnPoint) : 
	DualRectangle(spawnPoint), 
	state_(State::IDLE, State::RIGHT, State::SIDE)
{
	setup_animations(graphics);
}


Player::~Player() {
	for (auto iter = sprites_.begin(); iter != sprites_.end(); ++iter) {
		iter->second.reset();
	}
	sprites_.clear();
}


// this could use another helper function to reduce repetitiveness
void Player::setup_animations(Graphics& graphics) {

	setup_sprite(graphics, State::WALK, State::LEFT, State::SIDE, { 0,1,0,2 }, LEFT_FRAME, FRAME_LENGTH_MS);
	setup_sprite(graphics, State::WALK, State::LEFT, State::UP, { 3,4,3,5 }, LEFT_FRAME, FRAME_LENGTH_MS);
	setup_sprite(graphics, State::WALK, State::LEFT, State::DOWN, 7, LEFT_FRAME);
	setup_sprite(graphics, State::WALK, State::RIGHT, State::SIDE, { 0,1,0,2 }, RIGHT_FRAME, FRAME_LENGTH_MS);
	setup_sprite(graphics, State::WALK, State::RIGHT, State::UP, { 3,4,3,5 }, RIGHT_FRAME, FRAME_LENGTH_MS);
	setup_sprite(graphics, State::WALK, State::RIGHT, State::DOWN, 7, RIGHT_FRAME);

	setup_sprite(graphics, State::IDLE, State::LEFT, State::SIDE, 0, LEFT_FRAME);
	setup_sprite(graphics, State::IDLE, State::LEFT, State::UP, 3, LEFT_FRAME);
	setup_sprite(graphics, State::IDLE, State::LEFT, State::DOWN, 7, LEFT_FRAME);
	setup_sprite(graphics, State::IDLE, State::RIGHT, State::SIDE, 0, RIGHT_FRAME);
	setup_sprite(graphics, State::IDLE, State::RIGHT, State::UP, 3, RIGHT_FRAME);
	setup_sprite(graphics, State::IDLE, State::RIGHT, State::DOWN, 7, RIGHT_FRAME);

	setup_sprite(graphics, State::RISE, State::LEFT, State::SIDE, 1, LEFT_FRAME);
	setup_sprite(graphics, State::RISE, State::LEFT, State::UP, 4, LEFT_FRAME);
	setup_sprite(graphics, State::RISE, State::LEFT, State::DOWN, 6, LEFT_FRAME);
	setup_sprite(graphics, State::RISE, State::RIGHT, State::SIDE, 1, RIGHT_FRAME);
	setup_sprite(graphics, State::RISE, State::RIGHT, State::UP, 4, RIGHT_FRAME);
	setup_sprite(graphics, State::RISE, State::RIGHT, State::DOWN, 6, RIGHT_FRAME);

	setup_sprite(graphics, State::FALL, State::LEFT, State::SIDE, 2, LEFT_FRAME);
	setup_sprite(graphics, State::FALL, State::LEFT, State::UP, 5, LEFT_FRAME);
	setup_sprite(graphics, State::FALL, State::LEFT, State::DOWN, 6, LEFT_FRAME);
	setup_sprite(graphics, State::FALL, State::RIGHT, State::SIDE, 2, RIGHT_FRAME);
	setup_sprite(graphics, State::FALL, State::RIGHT, State::UP, 5, RIGHT_FRAME);
	setup_sprite(graphics, State::FALL, State::RIGHT, State::DOWN, 6, RIGHT_FRAME);

}


void Player::setup_sprite(
	Graphics& graphics,
	State::Movement movement,
	State::Horizontality horizontal,
	State::Verticality vertical,
	std::vector<int> xFrames, int yFrame, 
	float frameLength)
{
	sprites_[State(movement, horizontal, vertical)] = 
		std::make_shared<AnimatedSprite>(
		graphics, SPRITE_PATH, Color(0, 0, 0), xFrames, yFrame,
		SPRITE_WIDTH_PIXELS, SPRITE_HEIGHT_PIXELS, FRAME_LENGTH_MS);
}


void Player::setup_sprite(
	Graphics& graphics,
	State::Movement movement,
	State::Horizontality horizontal,
	State::Verticality vertical,
	int xFrame, int yFrame)
{
	sprites_[State(movement, horizontal, vertical)] =
		std::make_shared<Sprite>(
		graphics, SPRITE_PATH, Color(0, 0, 0), xFrame, yFrame,
		SPRITE_WIDTH_PIXELS, SPRITE_HEIGHT_PIXELS);
}


void Player::move_left() {
	if (on_ground())
		acceleration_.x = -WALKING_ACCELERATION_X;
	else if(acceleration_.x >= 0.0f)
		acceleration_.x = -REVERSE_AIRBORNE_ACCELERATION_X;
	state_.movement_ = State::WALK;
	state_.horizontality_ = State::LEFT;
}


void Player::move_right() {
	if (on_ground())
		acceleration_.x = WALKING_ACCELERATION_X;
	else if(acceleration_.x <= 0.0f)
		acceleration_.x = REVERSE_AIRBORNE_ACCELERATION_X;
	state_.movement_ = State::WALK;
	state_.horizontality_ = State::RIGHT;
}


void Player::stop_moving() {
	acceleration_.x = 0.0f;
	state_.movement_ = State::IDLE;
}


void Player::start_jump() {
	if (on_ground() && state_.jump_.recovered_) {
		velocity_.y = -MAX_JUMP_VELOCITY_Y;
		state_.movement_ = State::RISE;
		state_.jump_.grounded_ = false;
	}
	state_.jump_.recovered_ = false;
}


void Player::decrease_jump() {
	if (velocity_.y < -MIN_JUMP_VELOCITY_Y)
		velocity_.y = -MIN_JUMP_VELOCITY_Y;
	state_.jump_.recovered_ = true;
}


void Player::look_horizontal() {
	state_.verticality_ = State::SIDE;
	state_.enter_door_ = true;
}


void Player::look_up() {
	state_.verticality_ = State::UP;
}


void Player::look_down() {
	state_.verticality_ = State::DOWN;
}


void Player::fire() {}


void Player::set_position(const Point2D& pos) {
	//position_ = pos;
}


void Player::spawn_at(const Point2D& pos) {
	
}


const int Player::get_x() const {
	return position_.x;
}


const int Player::get_y() const {
	return position_.y;
}


const int Player::width() const {
	return SPRITE_WIDTH_PIXELS;
}


const int Player::height() const {
	return SPRITE_HEIGHT_PIXELS;
}


const int Player::center_x() const {
	return position_.x + SPRITE_WIDTH_PIXELS / 2;
}


const int Player::center_y() const {
	return position_.y + SPRITE_HEIGHT_PIXELS / 2;
}


const Point2D Player::center_position() const {
	return { 
		position_.x + SPRITE_WIDTH_PIXELS / 2, 
		position_.y + SPRITE_HEIGHT_PIXELS / 2 
	};
}


bool Player::on_ground() {
	return state_.jump_.grounded_;
}


bool Player::can_enter() {
	return state_.verticality_ == state_.DOWN && state_.enter_door_;
}


void Player::has_entered() {
	state_.enter_door_ = false;
	velocity_.x = 0.0f;
	acceleration_.x = 0.0f;
}


void Player::handle_input(Input& input) {

	if (input.is_key_held(SDL_SCANCODE_LEFT) && input.is_key_held(SDL_SCANCODE_RIGHT))
		stop_moving();
	else if (input.is_key_held(SDL_SCANCODE_LEFT))
		move_left();
	else if (input.is_key_held(SDL_SCANCODE_RIGHT))
		move_right();
	else
		stop_moving();

	if (input.is_key_held(SDL_SCANCODE_UP) && input.is_key_held(SDL_SCANCODE_DOWN))
		look_horizontal();
	else if (input.is_key_held(SDL_SCANCODE_UP))
		look_up();
	else if (input.is_key_held(SDL_SCANCODE_DOWN))
		look_down();
	else
		look_horizontal();

	if (input.was_key_pressed(SDL_SCANCODE_Z))
		start_jump();
	else if (input.was_key_released(SDL_SCANCODE_Z))
		decrease_jump();
	
	if (input.was_key_pressed(SDL_SCANCODE_X))
		fire();
}


void Player::react_top_collision(std::unique_ptr<Tile>& tile) {
	velocity_.y = 0.0f;
}


void Player::react_bottom_collision(std::unique_ptr<Tile>& tile) {
	velocity_.x *= tile->friction();
	state_.jump_.grounded_ = true;
	velocity_.y = 0.0f;
}


void Player::react_left_collision(std::unique_ptr<Tile>& tile) {
	velocity_.x = 0.0f;
}


void Player::react_right_collision(std::unique_ptr<Tile>& tile) {
	velocity_.x = 0.0f;
}


State& Player::state() {
	return state_;
}


void Player::update(int elapsedTime) {

	if (velocity_.x < -MAX_VELOCITY_X)
		velocity_.x = -MAX_VELOCITY_X;
	else if (velocity_.x > MAX_VELOCITY_X)
		velocity_.x = MAX_VELOCITY_X;

	if (velocity_.y != 0.0f)
		state_.jump_.grounded_ = false;
	if (velocity_.y > TERMINAL_VELOCITY)
		velocity_.y = TERMINAL_VELOCITY;

	if (!on_ground())
		velocity_.x *= AIR_RESISTANCE;

	state_.update_state(velocity_, acceleration_);
	sprites_[state_]->update(elapsedTime);
}


void Player::draw(Graphics& graphics, int x, int y) {
	sprites_[state_]->draw(graphics, x, y);
}

