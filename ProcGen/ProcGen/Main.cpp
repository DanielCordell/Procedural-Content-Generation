#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "TerrainGenerator.h"
#include "TileMap.h"
#include "Sizes.h"

void printStuff(std::string x, std::string y, TileMap& map) {
	int x1 = stoi(x);
	int y1 = stoi(y);

	auto t = map.GetTile(x1, y1);
	std::cout << "X: " << t.position.x << " Y: " << t.position.y << std::endl;
	std::cout << "Height: " << t.height << "m" << std::endl;
	std::cout << "Temperature: " << t.temperature << "degrees C" << std::endl;
	std::cout << "Rainfall: " << t.rainfall << "cm\n\n" << std::endl;
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	TerrainGenerator::InitialiseNoise();

	//This will take a while!
	TileMap map(XMAX, YMAX);

	sf::RenderWindow window(sf::VideoMode{XMAX,YMAX}, "Procedural Terrain Generation");


	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::MouseButtonPressed) {
				printStuff(std::to_string(e.mouseButton.x), std::to_string(e.mouseButton.y), map);
			}
		}
		window.clear();
		window.draw(map);
		window.display();
	}
}
