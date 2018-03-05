#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <map>

//Biome Graphs
//https://i.imgur.com/OYYEStT.png
//http://thewillis.weebly.com/uploads/5/8/7/4/58745719/9237160_orig.jpg
//https://upload.wikimedia.org/wikipedia/commons/6/68/Climate_influence_on_terrestrial_biome.svg

enum class Biome {
 //	Biome Name		  Grass Color
	Rainforest,		//Deep Green
	Swamp,			//Blueish Brownish Green
	ForestSeasonal,	//Brownish Green
	Forest,			//Bright Green
	Savanna,		//Greenish Brown
	Woods,			//Bright 
	Taiga,			//Whiteish Brown
	Desert,			//Yellow
	DesertGrassy,	//Yellowish Green
	Tundra,			//White/Grey
	Volcano,		//Reddish Brown - Override other biomes if heightmap over value (hot) 
	Mountain,		//Whiteish Brown - Override other biomes if heightmap over value (cold)
	Ocean			//Blue Override other biomes of heightmap under value
};

//The colour of grass tiles in biomes will be dependant on the biome itself.
//A biome can have multiple different tile types in it (so grass + snow for a tundra).

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
	friend class TerrainGenerator;
private:
public:
	Ground groundType;
	Biome biome;
	bool isCoast;				//If sand && close to ocean
	int height;					//Height above sea level (km)
	unsigned rainfall;			//Annual precipitation (cm)
	unsigned temperature;		//Average temperatuer (Degrees C)
	
	sf::Vector2i position;		//The position of this tile in the tilemap
	sf::VertexArray vArr;		//Array of the 4 vertices that make up this tile.
public:
	//Constructs a tile based on the x and y coordinates (uses the TerrainGenerator static class).
	Tile(unsigned x, unsigned y, sf::VertexArray vArr);
};


const std::map<Biome, std::string> BiomeNameMap{
	{ Biome::Rainforest, "Rainforest" },
	{ Biome::Swamp, "Swamp" },
	{ Biome::ForestSeasonal, "Seaonal Forest" },
	{ Biome::Forest, "Forest" },
	{ Biome::Savanna, "Savanna" },
	{ Biome::Woods, "Woods" },
	{ Biome::Taiga, "Taiga" },
	{ Biome::Desert, "Desert" },
	{ Biome::DesertGrassy, "DesertGrassy" },
	{ Biome::Tundra, "Tundra" },
	{ Biome::Volcano, "Volcano" },
	{ Biome::Mountain, "Mountain" },
	{ Biome::Ocean, "Ocean" }
};

const std::map<Ground, std::string> GroundNameMap{
	{Ground::Dirt, "Dirt"},			// Brown Color
	{ Ground::Grass,"Grass"	},		// Coloured based on biome
	{ Ground::Stone,"Stone" },		// Coloured based on biome?
	{ Ground::Snow, "Snow"},	// Blueish White/Grey color
	{ Ground::SandYellow, "Yellow Sand"},		// Yellow
	{ Ground::SandRed, "Red Sand"},		// Red
	{ Ground::WaterDeep, "Deep Water"},		// Dark Blue
	{ Ground::WaterShallow, "Shallow Water"}// Light Blue
};