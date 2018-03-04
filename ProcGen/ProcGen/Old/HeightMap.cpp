/*
#include "HeightMap.h"

//Functions related to generating heightmap



sf::Color heightToColor(double height)
{
	if (height <= 0.34) return Colors::DarkBlue;
	if (height > 0.34 && height < 0.37)		return Colors::LightBlue;
	if (height >= 0.37 && height < 0.38)	return Colors::Sand; 
	if (height >= 0.38 && height < 0.43)	return Colors::LightGreen;
	if (height >= 0.43 && height < 0.48)	return Colors::Green; 
	if (height >= 0.48 && height < 0.52)	return Colors::DarkGreen; 
	if (height >= 0.52 && height < 0.57)	return Colors::Stone;
	return Colors::Snow;
}

sf::Color rangeToColor(int x, int y, FastNoise & noiseHeight)
{
	auto noiseval = noiseHeight.GetNoise(x, y);
	double height = (noiseval + 1) / 2.0f;
	double distFromCentre = sqrt(pow(centre.x - x, 2) + pow(centre.y - y, 2));
	if (distFromCentre > maxDistance) {
		distFromCentre = maxDistance;
	}
	double circleGradient = (maxDistance - distFromCentre) / maxDistance;
	height *= circleGradient;

	return heightToColor(height);

}

const sf::Color Colors::DarkBlue(0, 95, 152);
const sf::Color Colors::LightBlue(0, 119, 190);
const sf::Color Colors::Sand(239, 221, 111);
const sf::Color Colors::LightGreen(1, 166, 17);
const sf::Color Colors::Green(1, 142, 14);
const sf::Color Colors::DarkGreen(1, 116, 17);
const sf::Color Colors::Stone(128, 132, 135);
const sf::Color Colors::Snow(238, 233, 233);
*/