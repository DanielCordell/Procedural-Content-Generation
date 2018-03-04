#pragma once

#include "FastNoise.h"

struct TerrainGenerator {
private:
	static FastNoise height;
	static FastNoise precipitation;
	static FastNoise temperature;

	//Gets the noise value (normalised to fall between 0 and 1).
	//I have this because fastnoise defaults to -1 to 1, and while I could fix it after I get the value, this way I don't need to remember.
	//Private as you should use the "generate" function (NYI)
	static float getHeight(float x, float y);
	static float getPrecipitation(float x, float y);
	static float getTemperature(float x, float y);

public:
	static void InitialiseNoise();

};
