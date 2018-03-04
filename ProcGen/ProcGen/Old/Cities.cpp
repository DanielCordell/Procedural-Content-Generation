
/*
#include "Cities.h"
#include "HeightMap.h"

void Cities::Clear() {
	cities.clear();
}

void Cities::Init()
{
	tex.loadFromFile("Resources/town.png");
}

void Cities::Add(sf::Vector2i position, CitySize size)
{
	cities.push_back(std::make_shared<City>(position, tex, size));
}

void Cities::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//std::cout << "Length: " << cities.size() << "\n";
	for (std::shared_ptr<City> city : cities) {
		target.draw(*city, states);
	}
}


bool CanHaveVillage(sf::Vertex position)
{
	sf::Color color = position.color;
	if (color == Colors::LightGreen || color == Colors::Green || color == Colors::DarkGreen || color == Colors::Stone) return true;
	return false;
}

CitySize ChooseCitySize(int & small, int & med, int & large)
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
*/