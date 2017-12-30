#include "Cities.h"
#include "HeightMap.h"
#include <iostream>

bool CanHaveVillage(sf::Vertex position)
{
	sf::Color color = position.color;
	if (color == Colors::LightGreen || color == Colors::Green || color == Colors::DarkGreen || color == Colors::Stone) return true;
	return false;
}

std::vector<sf::Vector2i> getCityCoords(sf::Vector2i position) {
	std::vector<sf::Vector2i> cityCoords;
	//TODO: Implement size difference (small/med/large)
	for (int x = -3; x <= 3; ++x) {
		for (int y = -3; y <= 3 ; ++y) {
			if (abs(x) + abs(y) <= 3) cityCoords.push_back({ position.x + x, position.y + y });
		}
	}

	//TODO: City class

	for (auto a : cityCoords) std::cout << a.x << " " << a.y << std::endl;
	std::cout << "\n";
	return cityCoords;
}