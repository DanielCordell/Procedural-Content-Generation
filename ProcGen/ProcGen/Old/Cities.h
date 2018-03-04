#pragma once
/*
#include <vector>
#include <SFML/Graphics.hpp>

#include "City.h"
#include <memory>
/*
class Cities : public sf::Drawable {
private:
	std::vector<std::shared_ptr<City>> cities;
	sf::Texture tex;
public:
	void Clear();
	void Init();
	void Add(sf::Vector2i position, CitySize size);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

bool CanHaveVillage(sf::Vertex position);

CitySize ChooseCitySize(int& small, int& med, int& large);
*/