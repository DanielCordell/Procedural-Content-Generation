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
