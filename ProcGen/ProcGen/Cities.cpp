#include "Cities.h"
#include "HeightMap.h"
#include <iostream>

void Cities::clear() {
	cities.clear();
}

void Cities::init()
{
	tex.loadFromFile("Resources/town.png");
}

void Cities::add(sf::Vector2i position, CitySize size)
{
	std::cout << "ADDING CITY of size " <<  size << "\n";
	std::cout << "Length Before: " << cities.size() << "\n";
	
	cities.push_back(std::make_shared<City>(position, tex, size));
	std::cout << "Length After: " << cities.size() << "\n";
}

void Cities::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//std::cout << "Length: " << cities.size() << "\n";
	for (std::shared_ptr<City> city : cities) {
		std::cout << "DRAWING1\n";
		target.draw(*city, states);
	}
}


bool CanHaveVillage(sf::Vertex position)
{
	sf::Color color = position.color;
	if (color == Colors::LightGreen || color == Colors::Green || color == Colors::DarkGreen || color == Colors::Stone) return true;
	return false;
}

CitySize chooseCitySize(int & small, int & med, int & large)
{
	while (true) {
		int whichToChoose = rand() % 3;
		if (whichToChoose == 0 && small > 0) {
			--small;
			return Small;
		}
		if (whichToChoose == 1 && med > 0) {
			--med;
			return Medium;
		}
		if (whichToChoose == 2 && large > 0) {
			--large;
			return Large;
		}
	}
}