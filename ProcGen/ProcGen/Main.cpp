#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <mutex>
#include <iostream>

#include "FastNoise.h"

#define XMAX 2560.0
#define YMAX 1440.0
#define SCALE 1.4


sf::Color getColor(double val) {
	if (val <= 0.34) return sf::Color(0, 119, 190); // Deep Blue
	if (val > 0.34 && val < 0.37) return sf::Color(0, 119, 190); // Light Blue
	if (val >= 0.37 && val < 0.38) return sf::Color(239, 221, 111); // Sand
	if (val >= 0.38 && val < 0.43) return sf::Color(1, 166, 17); //V Light Green
	if (val >= 0.43 && val < 0.48) return sf::Color(1, 142, 14); // Light Green
	if (val >= 0.48 && val < 0.52) return sf::Color(1, 116, 17); // Dark Green
	if (val >= 0.52 && val < 0.57) return sf::Color(128, 132, 135);
	return sf::Color(238, 233, 233); // Snow
}

sf::Color rangeToColor(int x, int y, FastNoise& noiseHeight) {
	auto noiseval = noiseHeight.GetNoise(x, y);
	double height = (noiseval + 1) / 2.0f;

	sf::Vector2<double> centre{ XMAX / 2.0f, YMAX / 2.0f };

	double distFromCentre = sqrt(pow(centre.x - x, 2) + pow(centre.y - y, 2));
	double maxDistance = sqrt(pow(centre.x - std::max(XMAX, YMAX) / 2.0f, 2) + pow(centre.y - std::max(XMAX, YMAX) / 2.0f, 2));
	if (distFromCentre > maxDistance){
		distFromCentre = maxDistance;
	}
	double circleGradient = (maxDistance - distFromCentre) / maxDistance;
	height *= circleGradient;

	return getColor(height);
	
}

void populate(sf::VertexArray& grid, FastNoise& noiseHeight) {

	noiseHeight.SetSeed(time(nullptr));
	for (int x = 0; x < XMAX; ++x) {
		for (int y = 0; y < YMAX; ++y) {
			sf::Color color = rangeToColor(x, y, noiseHeight);
			for (int q = 0; q < 4; ++q) {
				auto& vertex = grid[x*YMAX * 4 + y * 4 + q];
				//Hacky way to get each coordinate.
				vertex.position = sf::Vector2f( static_cast<float>(x + (q>1? 1:0 )), static_cast<float>(y + (q==1 || q==2? 1:0)));
				vertex.color = color;
			}
		}
	}
}


int main() {
	FastNoise noiseHeight;

	noiseHeight.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseHeight.SetFractalOctaves(4);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Noise");
	sf::View view = window.getView();
	view.zoom(1.f / SCALE);
	view.setCenter(XMAX / 2.f, YMAX / 2.f);
	window.setView(view);
	sf::VertexArray grid;
	try {
		grid = sf::VertexArray(sf::PrimitiveType::Quads, XMAX * YMAX * 4);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Max Size: " << static_cast<int>(std::vector<sf::PrimitiveType>().max_size()) << " " << "Actual Size: " << XMAX*YMAX * 4;
		return 0;
	}
	//Initial population
	populate(grid, noiseHeight);

	sf::Event event;
	while (true) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return 0;
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::S) {
					sf::RenderTexture tex;
					tex.create(XMAX / 2.f, YMAX / 2.f);
					tex.clear();
					tex.setView(view);
					tex.draw(grid);
					tex.display();
					tex.getTexture().copyToImage().saveToFile("../img.png");
					break;
				}
				else {
					populate(grid, noiseHeight);
				}

			}
			window.clear(sf::Color::Black);
			window.draw(grid);
			window.display();
		}
	}
}
