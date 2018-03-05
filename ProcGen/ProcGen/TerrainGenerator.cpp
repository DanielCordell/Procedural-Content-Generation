#include <cstdlib>

#include "TerrainGenerator.h"
FastNoise TerrainGenerator::height;
FastNoise TerrainGenerator::precipitation;
FastNoise TerrainGenerator::temperature;

void TerrainGenerator::InitialiseNoise() {
	// Using 3 different random numbers, otherwise the height, weather and temperature maps would all be the same!
	height.SetSeed(rand());
	precipitation.SetSeed(rand());
	temperature.SetSeed(rand());
}

float TerrainGenerator::getHeight(float x, float y) {
	return (height.GetNoise(x, y) + 1) / 2;

}

float TerrainGenerator::getPrecipitation(float x, float y) {
	return (precipitation.GetNoise(x, y) + 1) / 2;
}

float TerrainGenerator::getTemperature(float x, float y) {
	return (temperature.GetNoise(x, y) + 1) / 2;
}

void TerrainGenerator::GenerateTile(Tile * tile) {
	tile->height = 1000;
	tile->biome = Biome::Ocean;
	tile->groundType = Ground::WaterDeep;
	tile->isCoast = false;
	tile->rainfall = 100;
	tile->temperature = 25;
}