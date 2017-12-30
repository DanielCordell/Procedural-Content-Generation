#include <ctime>
#include <iostream>

#include "Populate.h"
#include "FastNoise.h"
#include "Sizes.h"
#include "HeightMap.h"
#include "Cities.h"

void PopulateHeightMap(sf::VertexArray & grid)
{
	FastNoise noiseHeight(time(nullptr));
	noiseHeight.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseHeight.SetFractalOctaves(4);

	for (int x = 0; x < XMAX; ++x) {
		for (int y = 0; y < YMAX; ++y) {
			sf::Color color = rangeToColor(x, y, noiseHeight);
			for (int q = 0; q < 4; ++q) {
				auto& vertex = grid[x*YMAX*4 + y*4 + q];
				//Hacky way to get each coordinate.
				vertex.position = sf::Vector2f(static_cast<float>(x + (q > 1 ? 1 : 0)), static_cast<float>(y + (q == 1 || q == 2 ? 1 : 0)));
				vertex.color = color;
			}
		}
	}
}

void PopulateCities(sf::VertexArray & grid)
{
	srand(time(nullptr));

	int numberOfCities = rand() % 3 + 2;
	for (int i = 0; i < numberOfCities; ++i) {
		bool foundCityLocation = false;
		sf::Vector2i position;
		while (!foundCityLocation) {
			position.x = rand() % int(XMAX * 0.6) + int(XMAX * 0.2);
			position.y = rand() % int(YMAX);
			std::cout << "Try to build city at: " << position.x << " " << position.y << std::endl;
			int gridIndex = position.x*YMAX * 4 + position.y * 4;
			auto vertex = grid[gridIndex];
			if (CanHaveVillage(vertex)) {
				foundCityLocation = true;
				std::cout << "New City " << position.x << " " << position.y << std::endl;
				for (int a = 0; a < 4; ++a) {
					auto toBlacken = getCityCoords(position);
					for (auto coord : toBlacken) {
						grid[coord.x*YMAX * 4 + coord.y * 4 + a].color = sf::Color::Black;
					}
				}
			}
		}
	}
}

