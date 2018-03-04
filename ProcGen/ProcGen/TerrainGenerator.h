#pragma once
#include <cstdlib>

#include "FastNoise.h"

struct TerrainGenerator {
	static FastNoise height;
	static FastNoise precipitation;
	static FastNoise temperature;

	static void InitialiseNoise();
};
