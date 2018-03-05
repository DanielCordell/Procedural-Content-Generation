#include "Tile.h"
#include "TerrainGenerator.h"

Tile::Tile(unsigned x, unsigned y, std::vector<sf::Vertex*>& vArr) : position(x, y) {
	this->vArr.resize(4);
	copy(vArr.begin(), vArr.end(), this->vArr.begin());
	TerrainGenerator::GenerateTile(this);
}
