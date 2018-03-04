#pragma once

//Biome Graphs
//https://i.imgur.com/OYYEStT.png
//http://thewillis.weebly.com/uploads/5/8/7/4/58745719/9237160_orig.jpg
//https://upload.wikimedia.org/wikipedia/commons/6/68/Climate_influence_on_terrestrial_biome.svg

enum Biome {
	Rainforest,
	Swamp,
	ForestSeasonal,
	Forest,
	Savanna,
	Woods,
	Taiga,
	Desert,
	DesertGrassy,
	Tundra,
	Volcano,		//Override other biomes if heightmap over value (hot)
	Mountain,		//Override other biomes if heightmap over value (cold)
	Ocean			//Override other biomes of heightmap under value
};

enum class Ground {
	Dirt,			// Brown Color
	Grass,			// Coloured based on biome
	Stone,			// Coloured based on biome?
	Snow,			// Blueish White/Grey color
	SandYellow,		// Yellow
	SandRed,		// Red
	WaterDeep,		// Dark Blue
	WaterShallow	// Light Blue
};


class Tile {
private:
	Ground groundType;
	Biome biome;
	bool isCoast;				//If sand && close to ocean
	int height;					//Height above sea level (km)
	unsigned rainfall;			//Annual precipitation (cm)
	unsigned temperature;		//Average temperatuer (Degrees C)
public:
	//Constructs a tile based on the x and y coordinates (uses the TerrainGenerator static class).
	Tile(unsigned x, unsigned y);
};

