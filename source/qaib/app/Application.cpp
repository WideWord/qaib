#include <qaib/app/Application.hpp>
#include <SFML/Window.hpp>

namespace qaib {

	int Application::exec() {
		window = std::shared_ptr<sf::Window>(new sf::Window(sf::VideoMode(800, 600), "Window"));

		while (window->isOpen()) {
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window->close();
			}
		}

		return 0;
	}

}