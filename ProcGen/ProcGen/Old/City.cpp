#include "City.h"


City::City(sf::Vector2i position, sf::Texture& tex, CitySize size) :  citySize(size)
{
	sprite.setTexture(tex);
	sprite.setScale(static_cast<int>(size) * 0.3, static_cast<int>(size) * 0.3);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setPosition(position.x, position.y);
}


void City::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

const sf::Vector2f City::GetLocation() const
{
	return sprite.getPosition();
}
