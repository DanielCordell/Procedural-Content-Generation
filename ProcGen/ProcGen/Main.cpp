#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <cstdlib>
#include <mutex>
#include <iostream>

#include "Sizes.h"
#include "Populate.h"
#include "Cities.h"
#include "CityDataRepresenter.h"

std::shared_ptr<bool> isGenerating;
bool doQuit = false;
sf::VertexArray grid;
void populate(Cities& cities) {
	while (!doQuit) {
		if (*isGenerating) {
			cities.Clear();
			//First Pass - Generate Heightmap
			PopulateHeightMap(grid);

			//Second Pass - Give Nature
			//PopulateNature(grid);

			//Third Pass - Give Cities
			PopulateCities(grid, cities);

			*isGenerating = false;
		}
	}
}


int main() {
	srand(time(nullptr));
	Cities cities;
	cities.Init();
	CityDataRepresenter cityData;
	isGenerating = std::make_shared<bool>(true);
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Noise", sf::Style::Default, sf::ContextSettings{0,0,2});
	sf::View view = window.getView();
	view.zoom(1.f / SCALE);
	view.setCenter(XMAX / 2.f, YMAX / 2.f);
	window.setView(view);
	try {
		grid = sf::VertexArray(sf::PrimitiveType::Quads, XMAX * YMAX * 4);
		for (int i = 0; i < grid.getVertexCount(); i++) {
			grid[i].color = sf::Color::Green;
		}
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Max Size: " << static_cast<int>(std::vector<sf::PrimitiveType>().max_size()) << " " << "Actual Size: " << XMAX*YMAX * 4;
		return 0;
	}
	std::thread thread = std::thread(populate, std::ref(cities));

	sf::Clock c;
	sf::Time sinceLastTick = sf::Time::Zero;
	while (true) {
		if (sinceLastTick.asSeconds() < 1 / 60.f) {
			sinceLastTick += c.restart();
			continue;
		}
		if (doQuit) break;

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				doQuit = true;
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				if (*isGenerating) break;
				if (event.key.code == sf::Keyboard::S) {
					sf::RenderTexture tex;
					tex.create(XMAX  * SCALE, YMAX  * SCALE);
					tex.clear();
					tex.setView(view);
					tex.draw(grid);
					tex.display();
					tex.getTexture().copyToImage().saveToFile("../img.png");
					break;
				}
				*isGenerating = true;
			}
		}
		window.clear(sf::Color::Black);			
		window.draw(grid);
		window.draw(cities);
		window.draw(cityData);

		window.display();
	}
	thread.join();
	window.close();
}
