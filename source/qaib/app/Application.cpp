#include <qaib/app/Application.hpp>
#include <SFML/Graphics.hpp>

#include <qaib/scene/Sprite.hpp>
#include <qaib/graphics/SceneRenderer.hpp>
#include <qaib/scene/Camera.hpp>

namespace qaib {

    
	int Application::exec() {
		window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "Window"));

		sf::Texture texture;
		texture.loadFromFile("../data/apple.jpg");
		
		auto scene = std::make_shared<SceneNode>();

		auto sprite = std::make_shared<Sprite>(texture);
		scene->addChild(sprite);

		auto cam = std::make_shared<Camera>();
		scene->addChild(cam);

		SceneRenderer renderer;

		while (window->isOpen()) {
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
                    closeButtonClicked.fire();
			}

			window->clear(sf::Color(0, 0, 255, 255));

			renderer.drawScene(window, scene, cam);

			window->display();

			cam->setPosition(cam->getPosition() + sf::Vector2f(-0.01f, -0.01f));
		}

		return 0;
	}

    void Application::quit() {
        window->close();
    }
    
}