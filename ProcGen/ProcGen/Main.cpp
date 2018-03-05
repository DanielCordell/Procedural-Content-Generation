#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "TerrainGenerator.h"
#include "TileMap.h"
#include "Sizes.h"
#include <SFML/Graphics/RenderWindow.hpp>

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	TerrainGenerator::InitialiseNoise();

	//This will take a while!
	TileMap map(XMAX, YMAX);

	sf::RenderWindow window(sf::VideoMode{ XMAX,YMAX }, "Procedural Terrain Generation");


	while (window.isOpen()) {
		std::string x;
		std::string y;
		int x1;
		int y1;
		
		try {
			std::cout << "Enter an x\n";
			std::cin >> x;
			x1 = stoi(x);

			std::cout << "Enter a y\n";
			y1 = stoi(y);
		}
		catch (std::exception ex) {
			break;
		}

		auto t = map.GetTile(x1, y1);
		std::cout << "X: " << t.position.x << " Y: " << t.position.y << std::endl;
		std::cout << "Height: " << t.height << "m" << std::endl;
		std::cout << "Temperature: " << t.temperature << "degrees C" << std::endl;
		std::cout << "Rainfall: " << t.rainfall << "cm\n\n" << std::endl;
	}
}
