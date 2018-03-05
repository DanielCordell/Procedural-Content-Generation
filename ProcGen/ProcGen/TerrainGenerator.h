#pragma once

#include "FastNoise.h"
#include "Tile.h"

//IS A FRIEND OF TILE
//This means that we can edit tile's members in 
class TerrainGenerator {
private:
	static FastNoise height;
	static FastNoise precipitation;
	static FastNoise temperature;

	//Gets the noise value (normalised to fall between the specified values).
	//I have this because fastnoise defaults to -1 to 1, and while I could fix it after I get the value, this way I don't need to remember.
	//Private as you should use the "generate" function (NYI)
	static int getHeight(float x, float y); // in m, normalised between -4000 and 8000
	static int getPrecipitation(float x, float y); // in cm, normalised between 0 and 450
	static int getTemperature(float x, float y); // in degrees celsius, normalised between -15 and 35

public:
	static void InitialiseNoise();
	static void GenerateTile(Tile* tile);
};
