#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "FastNoise.h"
#include <mutex>
#include <iostream>

#define XMAX 2560
#define YMAX 1440
#define SCALE 0.5

sf::Color biomeGrasslands(double val) {
	val += 0.2;
	if (val < -0.10) return sf::Color(0, 103, 165); // Deep Blue
	if (val >= -0.10 && val < 0.10) return sf::Color(0, 119, 190); // Light Blue
	if (val >= 0.10 && val < 0.15) return sf::Color(239, 221, 111); // Sand
	if (val >= 0.15 && val < 0.22) return sf::Color(1, 116, 17); //Dark Green
	if (val >= 0.22 && val < 0.33) return sf::Color(1, 142, 14); // Light Green
	if (val >= 0.33 && val < 0.43) return sf::Color(1, 166, 17); // V Light Green

	return sf::Color(238, 233, 233); // Snow
}

sf::Color biomeDesert(double val) {
	return biomeGrasslands(val);
	val += 0.2;
	if (val < -0.10) return sf::Color(0, 103, 165); // Deep Blue
	if (val >= -0.10 && val < 0.10) return sf::Color(0, 119, 190); // Light Blue
	if (val >= 0.10 && val < 0.33) return sf::Color(239, 221, 111); // Sand
	if (val >= 0.15 && val < 0.22) return sf::Color(231, 203, 124); //Dark Green
	return sf::Color(237, 190, 124); // Light Green
}

sf::Color biomeTundra(double val) {
	return biomeGrasslands(val);
	val += 0.2;
	if (val < -0.10) return sf::Color(23, 149, 137); // Deep Blue
	if (val >= -0.10 && val < 0.10) return sf::Color(6, 134, 154); // Light Blue
	if (val >= 0.10 && val < 0.15) return sf::Color(239, 221, 111); // Sand
	if (val >= 0.15 && val < 0.22) return sf::Color(1, 166, 17); // V Light Green
	return sf::Color(238, 233, 233); // Snow
}


sf::Color rangeToColor(int x, int y, FastNoise& noiseHeight, FastNoise& noiseBiome) {
	double height = noiseHeight.GetNoise(x, y);
	double biome = noiseBiome.GetNoise(x, y);

	if (biome < -0.33) return biomeDesert(height);
	if (biome >= -0.33 && biome < 0.33) return biomeGrasslands(height);
	return biomeTundra(height);
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
	FastNoise noiseHeight;
	FastNoise noiseBiome;

	noiseHeight.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseHeight.SetFractalOctaves(4);
	noiseHeight.SetFrequency(0.01);

	noiseBiome.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noiseBiome.SetFractalOctaves(4);
	noiseBiome.SetFrequency(0.005);
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
					std::cout << newNoiseType << std::endl;
					noiseHeight.SetNoiseType(newNoiseType);
				}
				else if (event.key.code == sf::Keyboard::S) {
					sf::RenderTexture tex;
					tex.create(XMAX, YMAX);
					tex.clear();
					tex.draw(grid);
					tex.display();
					tex.getTexture().copyToImage().saveToFile("../img.png");
					break;
				}
				populate(grid, noiseHeight, noiseBiome);
			}

		}

		window.clear(sf::Color::Black);
		window.draw(grid);
		window.display();
	}
}
