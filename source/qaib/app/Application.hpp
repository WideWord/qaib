#pragma once
#include <memory>

namespace sf {
	class Window;
}

namespace qaib {

	class Application {
	private:
		std::shared_ptr<sf::Window> window;
	public:
		int exec();
	};

}