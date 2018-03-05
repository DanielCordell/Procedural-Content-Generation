#include <vector>

#include "TileMap.h"
#include "TerrainGenerator.h"
#include "Sizes.h"

TileMap::TileMap(unsigned x, unsigned y) : vertexArray() {
	for (int i = 0; i < x; ++i) {
		tileMap.push_back(std::vector<std::unique_ptr<Tile>>());
		for (int j = 0; j < y; ++j) {
			std::vector<sf::Vertex*> vArr;
			for (int k = 0; k < 4; ++k) {
				vertexArray.append(sf::Vertex({static_cast<float>(x + (k > 1 ? 1 : 0)),
					static_cast<float>(y + (k == 1 || k == 2 ? 1 : 0))}));
				vArr.push_back(&vertexArray[i*YMAX * 4 + j * 4 + k]);
			}
			auto t = std::make_unique<Tile>(i, j, vArr);
			tileMap[i].push_back(std::move(t));
		}
	}
}

Tile TileMap::GetTile(unsigned x, unsigned y)
{
	return *tileMap[x][y].get();
}
