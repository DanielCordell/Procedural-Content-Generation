#pragma once
#include <memory>

#include <SFML/Graphics/VertexArray.hpp>

#include "Tile.h"

class TileMap {
private:
	//The drawable vertexArray
	//This should not be altered after constriction IN ANY WAY apart from via adjustments to the tilemap.
	//e.g. edit tilemap tile -> causes an edit to the vertexArray
	sf::VertexArray vertexArray;

	//The 2d array of tiles 
	//Each tile stores data about what is on the tile, biome, ground type (dirt/grass/sand/water/etc), and other such things.
	//Also stores a reference to the 4 vertices that make up the tile in the vertexarray.
	std::vector<std::vector<std::unique_ptr<Tile>>> tileMap;

public:
	TileMap(unsigned x = 1280, unsigned y = 720);

	Tile GetTile(unsigned x, unsigned y);
};
