#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace sf {
	class RenderWindow;
}

namespace qaib {

    class Application {
	private:
		sf::RenderWindow window;
	protected:
		virtual void init();
		virtual void doFrame(float deltaTime);
		virtual void closeButtonClicked();
	public:
		Application();

		int exec();
        void quit();

		inline sf::RenderWindow& getMainTarget() {
			return window;
		}
        
	};

}