#include <string>
#include <random>
#include <ctgmath>
#include "particleengine.h"
#include "fountain.h"
#include "ethereal.h"
#include "worldmap.h"
#include "camera.h"
#include "globals.h"


namespace {
	const std::string PARTICLE_BLUE = "content/particles/blue.bmp";
	const std::string PARTICLE_RED = "content/particles/red.bmp";
	const std::string PARTICLE_GREEN = "content/particles/green.bmp";
	const std::string PARTICLE_SHIMMER = "content/particles/shimmer.bmp";
	const int PARTICLE_WIDTH_PIXELS = 5;
	const int PARTICLE_HEIGHT_PIXELS = 5;
	const float PERCENT = 100.0f;
}


ParticleEngine::ParticleEngine() {}


ParticleEngine::ParticleEngine( 
	Graphics& graphics,
	const std::vector<std::string>& types,
	ParticlePattern patternType,
	int frequencyPerSec,
	const Point2D& pos) :
	NonPhysical(pos, {0,0}, {0,0}),
	particle_pattern_(patternType),
	particle_frequency_(1000 / frequencyPerSec),
	timer_(0), active_(true)
{
	for (size_t i = 0; i < types.size(); ++i) {
		if ( PARTICLE_BLUE.find(types[i]) !=  std::string::npos )
			add_sprite(graphics, PARTICLE_BLUE);
		else if ( PARTICLE_RED.find(types[i]) != std::string::npos )
			add_sprite(graphics, PARTICLE_RED);
		else if ( PARTICLE_GREEN.find(types[i]) != std::string::npos )
			add_sprite(graphics, PARTICLE_GREEN);
		else if ( PARTICLE_SHIMMER.find(types[i]) != std::string::npos )
			add_sprite(graphics, PARTICLE_SHIMMER);
	}
	total_particles_ = static_cast<int>(particle_sprites_.size());
}


ParticleEngine::~ParticleEngine() {
	for (auto iter = particles_.begin(); iter != particles_.end(); ++iter)
		iter->reset();
	particles_.clear();
	particles_.shrink_to_fit();

	for (auto iter = particle_sprites_.begin(); iter != particle_sprites_.end(); ++iter)
		iter->reset();
	particle_sprites_.clear();
	particle_sprites_.shrink_to_fit();
}


void ParticleEngine::add_sprite(Graphics& graphics, const std::string& type) {
	particle_sprites_.emplace_back(std::make_shared<Sprite>(
		graphics, type, Color(0, 255, 255), 0, 0,
		PARTICLE_WIDTH_PIXELS, PARTICLE_HEIGHT_PIXELS));
}


void ParticleEngine::activate() {
	active_ = true;
}


void ParticleEngine::deactivate() {
	active_ = false;
}


// this is cool, but is it correct?
std::shared_ptr<Particle> ParticleEngine::operator[](int i) {
	return particles_[i];
}


size_t ParticleEngine::particles_queued() {
	return particles_.size();
}


void ParticleEngine::add_particle() {
	int addParticle = timer_ / particle_frequency_;
	for (int i = 0; i < addParticle; ++i) {
		switch (particle_pattern_) {
		case PARTICLE_FOUNTAIN:
			particles_.emplace_back(add_fountain());
			break;
		case PARTICLE_ETHEREAL:
			particles_.emplace_back(add_ethereal());
			break;
		default: break;
		}
	}
}


std::shared_ptr<Particle> ParticleEngine::add_fountain() {
	int ptc = rand() % total_particles_;
	return std::make_shared<Fountain>(particle_sprites_[ptc], position_);
}


std::shared_ptr<Particle> ParticleEngine::add_ethereal() {
	int ptc = rand() % total_particles_;
	return std::make_shared<Ethereal>(particle_sprites_[ptc], position_);
}


void ParticleEngine::set_position(const Point2D& position) {
	position_ = position;
}


bool ParticleEngine::on_ground() {
	return false;
}


void ParticleEngine::set_fountain() {
	particle_pattern_ = PARTICLE_FOUNTAIN;
}


void ParticleEngine::set_ethereal() {
	particle_pattern_ = PARTICLE_ETHEREAL;
}


void ParticleEngine::update(int elapsedTime) {
	if (active_) {
		timer_ += elapsedTime;
		auto iter = particles_.begin();
		while (iter != particles_.end()) {
			iter->get()->update(elapsedTime);
			iter->get()->has_expired() ? iter = particles_.erase(iter) : ++iter;
		}
		add_particle();
		timer_ %= particle_frequency_;
	}
}


void ParticleEngine::draw(Graphics& graphics, int x, int y) {
	for (size_t i = 0; i < particles_.size(); ++i) {
		if (particles_[i]->is_visible()) {
			particles_[i]->draw(graphics,
				x + particles_[i]->position().x - position_.x,
				y + particles_[i]->position().y - position_.y);
		}
	}
}



