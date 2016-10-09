#pragma once
#include <SFML/Graphics.hpp>
#include <qaib/util/Typedef.hpp>

namespace sf {
	class RenderWindow;
}

namespace qaib {

    class Application {
	private:
		Ref<sf::RenderWindow> window;
		bool gui;
	protected:
		virtual void init();
		virtual void doFrame(float deltaTime);
		virtual void closeButtonClicked();
	public:
		Application(bool gui = true);

		int exec();
        void quit();

		inline sf::RenderWindow& getMainTarget() {
			return *(window.get());
		}
        
	};

}