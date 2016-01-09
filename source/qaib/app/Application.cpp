#include <qaib/app/Application.hpp>
#include <SFML/Graphics.hpp>


namespace qaib {

    
	int Application::exec() {
		window = new sf::RenderWindow(sf::VideoMode(800, 600), "Window");

		while (window->isOpen()) {
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					closeButtonClicked();
			}

			doFrame();

			window->display();
		}

		

		return 0;
	}

    void Application::quit() {
        window->close();
    }
    
	void Application::doFrame() {}

	void Application::closeButtonClicked(){
		quit();
	}
}