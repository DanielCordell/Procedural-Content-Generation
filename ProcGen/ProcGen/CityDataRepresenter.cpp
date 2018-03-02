#include "CityDataRepresenter.h"
#include "Sizes.h"
#include <iostream>

CityDataRepresenter::CityDataRepresenter() {
	background.setFillColor(sf::Color::Red);
	background.setSize({ 200,200 });
	background.setPosition(200, 200);
}

void CityDataRepresenter::DisplayCityData(City & city) {
	cityName.setString(city.cityName);
	cityPopulation.setString(std::to_string(city.cityPopulation));
	cityName.setPosition(XMAX - (256.f - cityName.getLocalBounds().width) / 2.f, YMAX - (144.f - cityName.getLocalBounds().height) / 2.f);
}

void CityDataRepresenter::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(background);
}
