#include "Tile.h"
#include "TerrainGenerator.h"

Tile::Tile(unsigned x, unsigned y, sf::VertexArray vArr): position(x,y), vArr(vArr) {
	TerrainGenerator::GenerateTile(this);
}
