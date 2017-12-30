#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Cities : public sf::Drawable {
private:
	std::vector<sf::Sprite> cities;
	sf::Texture tex;
public:
	void clear();
	void init();
	void add(sf::Vector2i position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

bool CanHaveVillage(sf::Vertex position);

