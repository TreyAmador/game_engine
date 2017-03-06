#include <sstream>
#include "worldmap.h"
//#include "core.h"
#include "body.h"
#include "player.h"
#include "particleengine.h"
#include "geometry.h"
#include "camera.h"
#include "graphics.h"
#include "globals.h"
#include "tinyxml2.h"


namespace {
	const int TILE_SIZE = 32;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
}


WorldMap::WorldMap() {
	map_area_.x = map_area_.y = 0;
	map_area_.w = SCREEN_WIDTH;
	map_area_.h = SCREEN_HEIGHT;
}


WorldMap::~WorldMap() {
	clear_map();
}


// pass in body vector also...
void WorldMap::load_map(Graphics& graphics, const std::string& mapname) {
	
	using namespace tinyxml2;
	//game_state_ = PAUSE;
	clear_map();
	std::string filename = "content/maps/" + mapname + ".tmx";
	XMLDocument doc;
	doc.LoadFile(filename.c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");
	int width = 0, height = 0, tilewidth = 0, tileheight = 0;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	mapNode->QueryIntAttribute("tilewidth", &tilewidth);
	mapNode->QueryIntAttribute("tileheight", &tileheight);

	map_area_.w = width * tilewidth;
	map_area_.h = height * tileheight;
	//background_sprite_ = std::make_shared<Sprite>(
	//	graphics, "content/maps/vertical.png", 
	//	0, 0, map_area_.width(), map_area_.height());

	tiles_.resize(height);
	for (size_t r = 0; r < tiles_.size(); ++r)
		tiles_[r].resize(width);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	while (pTileset) {

		int firstgid = 0, tilecount = 0;
		pTileset->QueryIntAttribute("firstgid", &firstgid);
		pTileset->QueryIntAttribute("tilecount", &tilecount);
		XMLElement* tilesetNode = pTileset->FirstChildElement("image");
		std::string imageSource = tilesetNode->Attribute("source");
		imageSource.replace(0, 2, "content");

		int tilesetWidth = 0, tilesetHeight = 0;
		tilesetNode->QueryIntAttribute("width", &tilesetWidth);
		tilesetNode->QueryIntAttribute("height", &tilesetHeight);
		int tilesetTileCols = tilesetWidth / tilewidth;
		int tilesetTileRows = tilesetHeight / tileheight;

		XMLElement* pLayer = mapNode->FirstChildElement("layer");
		while (pLayer) {
			bool collidable = std::string(pLayer->Attribute("name")).find("collidable") !=
				std::string::npos ? true : false;
			XMLElement* pData = pLayer->FirstChildElement("data");
			while (pData) {
				int i = 0;
				XMLElement* pTile = pData->FirstChildElement("tile");
				while (pTile) {
					int gid = 0;

					pTile->QueryIntAttribute("gid", &gid);
					if (gid >= firstgid && gid < firstgid + tilecount) {
						gid -= (firstgid - 1);

						tiles_[i/width][i%width] = Tile(
							graphics, imageSource,
							(gid-1)%tilesetTileCols,
							(gid-1)/tilesetTileCols,
							tilewidth, tileheight,
							(i%width)*tileheight,
							(i/width)*tilewidth,
							collidable);
					}
					++i;
					pTile = pTile->NextSiblingElement("tile");
				}
				pData = pData->NextSiblingElement("data");
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
		pTileset = pTileset->NextSiblingElement("tileset");
	}

	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	while (pObjectGroup) {
		std::string objectName = pObjectGroup->Attribute("name");

		if (objectName == "door") {
			XMLElement* pObject = pObjectGroup->FirstChildElement("object");
			while (pObject) {

				std::string destination = pObject->Attribute("name");
				int doorX = 0, doorY = 0, doorW = 0, doorH = 0;
				pObject->QueryIntAttribute("x", &doorX);
				pObject->QueryIntAttribute("y", &doorY);
				pObject->QueryIntAttribute("width", &doorW);
				pObject->QueryIntAttribute("height", &doorH);

				char delimiter = ',';
				std::vector<std::string> tokens;
				std::string coordinates = pObject->Attribute("type");
				split(tokens, coordinates, delimiter);
				int spawnX = std::stoi(tokens[0]);
				int spawnY = std::stoi(tokens[1]);

				doors_.emplace_back(destination, Point2D(spawnX,spawnY), doorX, doorY, doorW, doorH);
				pObject = pObject->NextSiblingElement("object");
			}
		}
		pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
	}
	//game_state_ = PLAY;
}


void WorldMap::split(std::vector<std::string>& tokens, std::string& unsplit, char delim) {
	std::stringstream ss(unsplit);
	std::string token;
	while (std::getline(ss, token, delim)) {
		if (!token.empty())
			tokens.push_back(token);
	}
}


// area of overlap between two rectangles
// SI = Max(0, Min(XA2, XB2) - Max(XA1, XB1)) * Max(0, Min(YA2, YB2) - Max(YA1, YB1))
std::unique_ptr<Tile> WorldMap::collisionsAABB(const Rectangle& rect) {
	int iRow = rect.top() / TILE_SIZE;
	int fRow = rect.bottom() / TILE_SIZE;
	int iCol = rect.left() / TILE_SIZE;
	int fCol = rect.right() / TILE_SIZE;
	for (int r = iRow; r <= fRow; ++r) {
		for (int c = iCol; c <= fCol; ++c) {
			if (tiles_[r][c].is_collidable()) {
				return std::make_unique<Tile>(tiles_[r][c]);
			}
		}
	}
	return nullptr;
}


std::vector<std::vector<Tile> >& WorldMap::tiles() {
	return tiles_;
}


void WorldMap::background_sprite(Graphics& graphics, int x, int y) {
	//background_sprite_->draw(graphics, x, y);
}


std::shared_ptr<std::string> WorldMap::door_collisions(Player& player) {
	for (size_t i = 0; i < doors_.size(); ++i) {
		if (doors_[i].in_threshold(player.collision_x()) && player.can_enter()) {
			player.has_entered();
			player.reposition_x(doors_[i].spawn_point().x);
			player.reposition_y(doors_[i].spawn_point().y);
			return std::make_shared<std::string>(doors_[i].destination());
		}
	}
	return nullptr;
}


void WorldMap::move_maps(Graphics& graphics, Player& player) {
	std::shared_ptr<std::string> filepath = door_collisions(player);
	if (filepath != nullptr)
		load_map(graphics, *filepath.get());
}


void WorldMap::clear_map() {
	for (size_t i = 0; i < tiles_.size(); ++i) {
		tiles_[i].clear();
		tiles_[i].shrink_to_fit();
	}
	tiles_.clear();
	tiles_.shrink_to_fit();

	background_sprite_.reset();

	doors_.clear();
	doors_.shrink_to_fit();
}


const int WorldMap::size() const {
	return TILE_SIZE;
}


const int WorldMap::width() const {
	return map_area_.width();
}


const int WorldMap::height() const {
	return map_area_.height();
}


const int WorldMap::top() const {
	return map_area_.top();
}


const int WorldMap::bottom() const {
	return map_area_.bottom();
}


const int WorldMap::right() const {
	return map_area_.right();
}


const int WorldMap::left() const {
	return map_area_.left();
}



//void WorldMap::update(Player& player, int elapsedTime) {
//	player.update(elapsedTime);
//	player.tile_collisions(*this, kinematics(player, elapsedTime));
//	door_collisions(player);
//}


void WorldMap::update(Body& body, int elapsedTime) {
	body.update(elapsedTime);
	body.tile_collisions(*this, kinematics(body,elapsedTime));
}

