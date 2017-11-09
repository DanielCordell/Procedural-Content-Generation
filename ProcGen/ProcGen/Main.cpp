#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <mutex>
#include <iostream>

#include "FastNoise.h"

#define XMAX 2560.0
#define YMAX 1440.0
#define SCALE 1.4

double sub;

float lerp(float a, float b, float f)
{
	return a * (1.0 - f) + b * f;
}


sf::Color getColor(double val) {
	val -= sub;
	if (val <= 0.36) return sf::Color(0, 119, 190); // Deep Blue
	if (val > 0.36 && val < 0.39) return sf::Color(0, 119, 190); // Light Blue
	if (val >= 0.39 && val < 0.40) return sf::Color(239, 221, 111); // Sand
	if (val >= 0.40 && val < 0.45) return sf::Color(1, 166, 17); //V Light Green
	if (val >= 0.45 && val < 0.50) return sf::Color(1, 142, 14); // Light Green
	if (val >= 0.50 && val < 0.55) return sf::Color(1, 116, 17); // Dark Green
	if (val >= 0.55 && val < 0.60) return sf::Color(128, 132, 135);
	return sf::Color(238, 233, 233); // Snow
}

sf::Color rangeToColor(int x, int y, FastNoise& noiseHeight, FastNoise& noiseBiome) {
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

	//return sf::Color(lerp(0, 255, pixel), lerp(0, 255, pixel), lerp(0, 255, pixel));
	return getColor(height);
	
}

void populate(sf::VertexArray& grid, FastNoise& noiseHeight, FastNoise& noiseBiome) {

	noiseHeight.SetSeed(time(nullptr));
	noiseBiome.SetSeed(time(nullptr));
	for (int x = 0; x < XMAX; ++x) {
		for (int y = 0; y < YMAX; ++y) {
			sf::Color color = rangeToColor(x, y, noiseHeight, noiseBiome);
			for (int q = 0; q < 4; ++q) {
				auto& vertex = grid[x*YMAX * 4 + y * 4 + q];
				vertex.position = sf::Vector2f( static_cast<float>(x + (q>1? 1:0 )), static_cast<float>(y + (q==1 || q==2? 1:0)));
				vertex.color = color;
			}
		}
	}
}


int main() {
	sub = 0;
	FastNoise noiseHeight;
	FastNoise noiseBiome;

	noiseHeight.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseHeight.SetFractalOctaves(4);

	noiseBiome.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseBiome.SetFractalOctaves(4);
	noiseBiome.SetFrequency(0.05);
	noiseBiome.SetCellularJitter(0.95);


	sf::RenderWindow window(sf::VideoMode(1280, 720),{});
	sf::View view = window.getView();
	view.zoom(1.f/SCALE);
	view.setCenter(XMAX / 2.f, YMAX / 2.f);
	window.setView(view);
	sf::Event event;
	sf::VertexArray grid;
	try {
		grid = sf::VertexArray(sf::PrimitiveType::Quads, XMAX * YMAX * 4);
	}
	catch(std::exception ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Max Size: " << static_cast<int>(std::vector<sf::PrimitiveType>().max_size()) << " " << "Actual Size: " << XMAX*YMAX*4;
	}
	populate(grid,noiseHeight,noiseBiome);
	while (true){
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					auto newNoiseType = static_cast<FastNoise::NoiseType>(int(noiseHeight.GetNoiseType()) + 1);
					if (newNoiseType > FastNoise::NoiseType::CubicFractal) newNoiseType = FastNoise::NoiseType::Value;
					noiseHeight.SetNoiseType(newNoiseType);
				}
				else if (event.key.code == sf::Keyboard::S) {
					sf::RenderTexture tex;
					tex.create(XMAX/2.f, YMAX/2.f);
					tex.clear();
					tex.setView(view);
					tex.draw(grid);
					tex.display();
					tex.getTexture().copyToImage().saveToFile("../img.png");
					break;
				}
				else if (event.key.code == sf::Keyboard::L) {
				}
				populate(grid, noiseHeight, noiseBiome);
			}

		}

		window.clear(sf::Color::Black);
		window.draw(grid);
		window.display();
	}
}
