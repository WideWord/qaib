#include <qaib/app/Application.hpp>



namespace qaib {

	Application::Application(): window(sf::VideoMode(800, 600), "Window") {

	}

	int Application::exec() {

		sf::Clock clock;

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					closeButtonClicked();
			}

			doFrame(clock.getElapsedTime().asSeconds());
			clock.restart();

			window.display();
		}

		

		return 0;
	}

    void Application::quit() {
        window.close();
    }
    
	void Application::doFrame(float deltaTime) {}

	void Application::closeButtonClicked(){
		quit();
	}
}