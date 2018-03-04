#pragma once
#include <cstdlib>

#include "FastNoise.h"

struct TerrainGenerator {
	static FastNoise height;
	static FastNoise precipitation;
	static FastNoise temperature;

	static void InitialiseNoise() {
		// Using 3 different random numbers, otherwise the height, weather and temperature maps would all be the same!
		height.SetSeed(rand());
		precipitation.SetSeed(rand());
		temperature.SetSeed(rand());
	}

};
