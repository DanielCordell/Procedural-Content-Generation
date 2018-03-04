
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "Sizes.h"

int main() {
	srand(time(nullptr));
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Noise", sf::Style::Default, sf::ContextSettings{ 0,0,2 });
	bool doQuit = false;

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
				//if (*isGenerating) break;
				if (event.key.code == sf::Keyboard::S) {
					sf::RenderTexture tex;
					tex.create(XMAX, YMAX);
					tex.clear();
					//tex.setView(view);
					//tex.draw(grid);
					tex.display();
					tex.getTexture().copyToImage().saveToFile("../img.png");
					break;
				}
				//*isGenerating = true;
			}
		}
		window.clear(sf::Color::Black);
		//window.draw(grid);
		//window.draw(cities);
		//window.draw(cityData);

		window.display();
	}
	//thread.join();
	window.close();
}
