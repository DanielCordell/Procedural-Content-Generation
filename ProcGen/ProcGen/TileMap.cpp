#include <iostream>

#include "TileMap.h"
#include "TerrainGenerator.h"
#include "Sizes.h"

TileMap::TileMap(unsigned x, unsigned y) : vertexArray(sf::PrimitiveType::Quads, x*y * 4) {
	for (int i = 0; i < x; ++i) {
		tileMap.push_back(std::vector<std::unique_ptr<Tile>>());
		for (int j = 0; j < y; ++j) {
			sf::VertexArray vArr;
			for (int k = 0; k < 4; ++k) {
				vArr.append(vertexArray[i*YMAX * 4 + j * 4 + k]);
			}
			auto t = std::make_unique<Tile>(i, j, vArr);
			tileMap[i].push_back(move(t));
		}
	}
}

Tile TileMap::GetTile(unsigned x, unsigned y)
{
	return *tileMap[x][y].get();
}
