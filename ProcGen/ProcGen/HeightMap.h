#pragma once

#include <algorithm>


#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "FastNoise.h"
#include "Sizes.h"

struct Colors {
	static const sf::Color DarkBlue;
	static const sf::Color LightBlue;
	static const sf::Color Sand;
	static const sf::Color LightGreen;
	static const sf::Color Green;
	static const sf::Color DarkGreen;
	static const sf::Color Stone;
	static const sf::Color Snow;
};


const sf::Vector2<double> centre{ XMAX / 2.0f, YMAX / 2.0f };
const double maxDistance = sqrt(pow(centre.x - std::max(XMAX, YMAX) / 2.0f, 2) + pow(centre.y - std::max(XMAX, YMAX) / 2.0f, 2));

sf::Color heightToColor(double height);

sf::Color rangeToColor(int x, int y, FastNoise& noiseHeight);