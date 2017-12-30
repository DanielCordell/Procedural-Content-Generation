#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

bool CanHaveVillage(sf::Vertex position);

std::vector<sf::Vector2i> getCityCoords(sf::Vector2i position);