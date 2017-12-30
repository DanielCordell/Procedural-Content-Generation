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

void Cities::add(sf::Vector2i position)
{
	sf::Sprite newCity;
	newCity.setTexture(tex);
	newCity.setOrigin(newCity.getGlobalBounds().width / 2.f, newCity.getGlobalBounds().height / 2.f);
	newCity.setPosition(position.x, position.y);
	float scaleFactor = (rand() % 3 + 1) * 0.3;
	newCity.setScale(scaleFactor, scaleFactor);
	cities.push_back(newCity);
}

void Cities::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto sprite : cities) target.draw(sprite, states);
}


bool CanHaveVillage(sf::Vertex position)
{
	sf::Color color = position.color;
	if (color == Colors::LightGreen || color == Colors::Green || color == Colors::DarkGreen || color == Colors::Stone) return true;
	return false;
}
