#include <ctime>
#include <iostream>

#include "Populate.h"
#include "FastNoise.h"
#include "Sizes.h"
#include "HeightMap.h"

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

void PopulateCities(sf::VertexArray & grid, Cities& cities)
{
	srand(time(nullptr));

	//Generate City Sizes
	int numberOfCities = rand() % 3;
	int smallNum = 1, medNum = 1, largeNum = 1;
	for (int temp = numberOfCities; temp > 0; --temp) {
		int whichToIncrease = rand() % 3;
		if (whichToIncrease == 0) ++smallNum;
		else if (whichToIncrease == 1) ++medNum;
		else largeNum++;
	}

	for (int i = 0; i < numberOfCities + 3; ++i) {
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

				//Choose a city size

				cities.add(position, chooseCitySize(smallNum, medNum, largeNum));
			}
		}
	}
}

