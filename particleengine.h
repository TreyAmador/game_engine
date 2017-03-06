#ifndef PARTICLE_ENGINE_H_
#define PARTICLE_ENGINE_H_
#include <vector>
#include <memory>
#include "nonphysical.h"
#include "particle.h"
#include "sprite.h"
class WorldMap;
class Camera;


enum ParticlePattern {
	PARTICLE_FOUNTAIN,
	PARTICLE_ETHEREAL
};

enum ParticleTiming {
	PARTICLE_RANDOM,
	PARTICLE_BURST
};


class ParticleEngine : public NonPhysical {

public:
	ParticleEngine();
	ParticleEngine(
		Graphics& graphics,
		const std::vector<std::string>& types,
		ParticlePattern patternType,
		int frequency,
		const Point2D& pos);

	virtual ~ParticleEngine();

	void add_sprite(Graphics& graphics, const std::string& type);

	void activate();
	void deactivate();
	
	std::shared_ptr<Particle> operator[](int i);
	size_t particles_queued();

	void add_particle();
	std::shared_ptr<Particle> add_fountain();
	std::shared_ptr<Particle> add_ethereal();

	virtual bool on_ground();

	void set_position(const Point2D& position);

	void set_fountain();
	void set_ethereal();

	virtual void update(int elapsedTime);
	virtual void draw(Graphics& graphics, int x, int y);

private:
	std::vector<std::shared_ptr<Particle> > particles_;
	std::vector<std::shared_ptr<Sprite> > particle_sprites_;
	ParticlePattern particle_pattern_;
	int total_particles_, particle_frequency_, timer_;
	bool active_;

};

#endif
