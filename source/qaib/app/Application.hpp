#pragma once
#include <memory>
#include <qaib/util/Event.hpp>

namespace sf {
	class RenderWindow;
}

namespace qaib {

    class Application {
	private:
		sf::RenderWindow* window;
	protected:
		virtual void doFrame();
		virtual void closeButtonClicked();
	public:
		int exec();
        void quit();

		inline sf::RenderWindow* getMainTarget() {
			return window;
		}
        
	};

}