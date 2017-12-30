#pragma once
#include <SFML/Graphics.hpp>

enum CitySize {
	Small = 1,
	Medium,
	Large
};

class City : public sf::Drawable {
private:
	sf::Sprite sprite;
public:
	City(sf::Vector2i position, sf::Texture& tex, CitySize size);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
