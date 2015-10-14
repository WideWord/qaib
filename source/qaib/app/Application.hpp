#pragma once
#include <memory>

namespace sf {
	class RenderWindow;
}

namespace qaib {

	class Application {
	private:
		std::shared_ptr<sf::RenderWindow> window;
	public:
		int exec();
	};

}