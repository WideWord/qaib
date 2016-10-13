#include <qaib/app/Application.hpp>



namespace qaib {

	Application::Application(bool gui) : gui(gui) {
		if (gui) {
			window = Ref<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1200, 1200), "qaib"));
		}
	}

	int Application::exec() {

		init();

		sf::Clock clock;

		while (true) {

			if (gui) {
				sf::Event event;
				while (window->pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						closeButtonClicked();
				}

				if (!window->isOpen()) break;

				doFrame(clock.getElapsedTime().asSeconds());
				clock.restart();

				window->display();
			} else {
				doFrame(1.0f / 30.0f);
			}
		}

		

		return 0;
	}

    void Application::quit() {
		if (gui) {
			window->close();
		}
    }
    
	void Application::doFrame(float deltaTime) {}

	void Application::init() {}

	void Application::closeButtonClicked(){
		quit();
	}
}