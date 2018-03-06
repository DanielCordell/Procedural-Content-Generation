#include <cstdlib>

#include "TerrainGenerator.h"
#include <iostream>

FastNoise TerrainGenerator::height;
FastNoise TerrainGenerator::precipitation;
FastNoise TerrainGenerator::temperature;

void TerrainGenerator::InitialiseNoise() {
	// Using 3 different random numbers, otherwise the height, weather and temperature maps would all be the same!
	height.SetSeed(rand());
	precipitation.SetSeed(rand());
	temperature.SetSeed(rand());
}

int TerrainGenerator::getHeight(float x, float y) {
	return static_cast<int>(floor(height.GetNoise(x, y) * 6000 + 2000));

}

int TerrainGenerator::getPrecipitation(float x, float y) {
	return static_cast<int>(floor(precipitation.GetNoise(x, y) * 225 + 225));
}

int TerrainGenerator::getTemperature(float x, float y) {
	return static_cast<int>(floor(temperature.GetNoise(x, y) * 25 + 10));
}

void TerrainGenerator::GenerateTile(Tile* tile) {
	int x = tile->position.x;
	int y = tile->position.y;
	tile->height = getHeight(x, y);
	tile->biome = Biome::Ocean;
	tile->groundType = Ground::WaterDeep;
	tile->isCoast = false;
	tile->rainfall = getPrecipitation(x, y);
	tile->temperature = getTemperature(x, y);

	int scaledHeight = 256 * (tile->height + 4000)/12000.f;
	sf::Color c(scaledHeight, scaledHeight, scaledHeight);
	for (auto vertex : tile->vArr) {
		vertex->color = c;
	}
}
