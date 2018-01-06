#pragma once
#include <SFML/Graphics.hpp>

#include "CityData.h"

enum CitySize {
	Small = 1,
	Medium,
	Large
};

class City : public sf::Drawable {
private:
	sf::Sprite sprite;
	bool isActive;
	CityData cityData;
public:
	City(sf::Vector2i position, sf::Texture& tex, CitySize size);
	void onClick();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
