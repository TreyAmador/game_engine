#ifndef WORLD_MAP_H_
#define WORLD_MAP_H_
#include <vector>
#include <memory>
#include <string>
#include "physics.h"
#include "tile.h"
#include "door.h"
#include "sprite.h"
class Player;
class Body;
class Camera;
class ParticleEngine;
struct Rectangle;


class WorldMap : private Physics {

public:
	WorldMap();
	virtual ~WorldMap();

	void load_map(Graphics& graphics, const std::string& mapName);
	void background_sprite(Graphics& graphics, int x, int y);
	std::unique_ptr<Tile> collisionsAABB(const Rectangle& rect);
	std::vector<std::vector<Tile> >& tiles();

	std::shared_ptr<std::string> door_collisions(Player& player);
	void move_maps(Graphics& graphics, Player& player);

	void split(std::vector<std::string>& tokens, std::string& unsplit, char delim);

	void clear_map();

	const int size() const;

	const int top() const;
	const int bottom() const;
	const int right() const;
	const int left() const;

	const int width() const;
	const int height() const;

	void update(Body& body, int elapsedTime);
	
private:
	std::vector<std::vector<Tile> > tiles_;
	std::shared_ptr<Sprite> background_sprite_;
	std::vector<Door> doors_;
	Rectangle map_area_;

};

#endif
