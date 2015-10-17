#pragma once
#include <memory>
#include <qaib/util/Event.hpp>

namespace sf {
	class RenderWindow;
}

namespace qaib {

    class Application : public EventHandler {
	private:
		std::shared_ptr<sf::RenderWindow> window;
	public:
		int exec();
        void quit();
        
        Event<> closeButtonClicked;
	};

}