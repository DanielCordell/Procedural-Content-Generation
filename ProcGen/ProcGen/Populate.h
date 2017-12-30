#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include "Cities.h"

void PopulateHeightMap(sf::VertexArray& grid);

void PopulateCities(sf::VertexArray & grid, Cities& cities);