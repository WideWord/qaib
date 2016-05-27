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

		sf::Texture rockTexture;
		sf::Sprite rockSprite;

		sf::View lastUsedView;

		float dotsPerGameMeter;

		void setupView(sf::RenderTarget& target);

		glm::vec2 cameraTarget;
	public:
		GameRenderer();

		inline void setGameWorld(GameWorld* world) {
			gameWorld = world;
		}
		inline GameWorld* getGameWorld() { return gameWorld; }

		virtual void drawFrame(sf::RenderTarget& target);

		glm::vec2 screenToWorldPosition(glm::vec2 screenPos);

		inline void setCameraTarget(glm::vec2 target) { cameraTarget = target; }
		inline glm::vec2 getCameraTarget() { return cameraTarget; }

	};

}