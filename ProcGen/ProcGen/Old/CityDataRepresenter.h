#pragma once

#include "City.h"

class CityDataRepresenter: public sf::Drawable {
private:
	sf::RectangleShape background;
	sf::Text cityName;
	sf::Text cityPopulation;
public:

	CityDataRepresenter();
	void DisplayCityData(City& city);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
