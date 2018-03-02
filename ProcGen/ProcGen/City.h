#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class CityDataRepresenter;

enum CitySize {
	Small = 2,
	Medium = 3,
	Large = 4
};

class City : public sf::Drawable {
	friend class CityDataRepresenter;
private:
	sf::Sprite		sprite;	
	//Data about the city (maybe will make a struct later)
	std::string		cityName;
	CitySize		citySize;
	int				cityPopulation;



public:
	City(sf::Vector2i position, sf::Texture& tex, CitySize size);
	void Populate();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const sf::Vector2f GetLocation() const;
	const bool IsActive() const;
};
