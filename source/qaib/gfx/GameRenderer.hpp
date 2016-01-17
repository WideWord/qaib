#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

namespace qaib {

	class GameWorld;

	class GameRenderer {
	private:
		GameWorld* gameWorld;
		sf::Texture pawnTexture;
		sf::Sprite pawnSprite;

		sf::Texture sandTexture;
		sf::Sprite sandSprite;

		sf::View lastUsedView;

		float dotsPerGameMeter;

		void setupView(sf::RenderTarget& target);
	public:
		GameRenderer();

		inline void setGameWorld(GameWorld* world) {
			gameWorld = world;
		}
		inline GameWorld* getGameWorld() { gameWorld; }

		virtual void drawFrame(sf::RenderTarget& target);

		glm::vec2 screenToWorldPosition(glm::vec2 screenPos);
	};

}