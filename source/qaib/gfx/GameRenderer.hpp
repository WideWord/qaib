#pragma once

#include <SFML/Graphics.hpp>

namespace qaib {

	class GameWorld;

	class GameRenderer {
	private:
		GameWorld* gameWorld;
		sf::Texture pawnTexture;
		sf::Sprite pawnSprite;
	public:
		GameRenderer();

		inline void setGameWorld(GameWorld* world) {
			gameWorld = world;
		}
		inline GameWorld* getGameWorld() { gameWorld; }

		virtual void drawFrame(sf::RenderTarget* target);
	};

}