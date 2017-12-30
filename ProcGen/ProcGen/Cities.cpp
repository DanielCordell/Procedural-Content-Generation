#include "Cities.h"
#include "HeightMap.h"
#include <iostream>

void Cities::clear() {
	cities.clear();
}

//Todo: Create a City Class so sizes can be enum based or something
void Cities::init()
{
	tex.loadFromFile("Resources/town.png");
}

void Cities::add(sf::Vector2i position, CitySize size)
{
	City newCity(position, tex, size);
	cities.push_back(newCity);
}

void Cities::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (City city : cities) target.draw(city, states);
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
