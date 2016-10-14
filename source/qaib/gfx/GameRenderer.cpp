#include <qaib/gfx/GameRenderer.hpp>

#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/Bullet.hpp>
#include <qaib/game/Obstruction.hpp>
#include <qaib/util/VectorConversion.hpp>


#include "resources.hpp"


namespace qaib {

	GameRenderer::GameRenderer() {



		pawnTexture.loadFromMemory(playerTextureData, playerTextureSize);
		pawnSprite.setTexture(pawnTexture);
		pawnSprite.setOrigin(103.5f, 103.5f);

        sandTexture.loadFromMemory(sandTextureData, sandTextureSize);
		sandTexture.setRepeated(true);

        rockTexture.loadFromMemory(rockTextureData, rockTextureSize);
        rockTexture.setRepeated(true);

        rockSprite.setTexture(rockTexture);
        rockSprite.setTextureRect(sf::IntRect(0, 0, 256 * 100, 256 * 100));
        rockSprite.setPosition(-100, -100);
        rockSprite.setScale(1 / 100.0f, 1 / 100.0f);


		dotsPerGameMeter = 75;
	}

	void GameRenderer::drawFrame(sf::RenderTarget& target) {

		target.clear();

		setupView(target);

		target.draw(rockSprite);

        {
            auto radius = gameWorld->getWorldSize() * 0.5f;

            sf::CircleShape sand(radius, 80);
            sand.setPosition(-radius, -radius);

            //sand.setFillColor(sf::Color::Yellow);
            sand.setTexture(&sandTexture);
            sand.setTextureRect(sf::IntRect(0, 0, 256 * (int)radius, 256 * (int)radius));

            target.draw(sand);
        }

        {
            auto& obstructions = gameWorld->getObstructions();

            for (auto obstruction : obstructions) {

                sf::RenderStates states;
                states.transform = obstruction->getSFTransform();
                //states.transform = states.transform.scale(1.0f / 200.0f, 1.0f / 200.0f);
                states.texture = &rockTexture;


                target.draw(obstruction->getPoints(), 3, sf::Triangles, states);

            }
        }

		auto& pawns = gameWorld->getPawns();
		for (auto pawn : pawns) {
			sf::RenderStates states;
			states.transform = pawn->getSFTransform();
			states.transform = states.transform.scale(1.0f / 200.0f, 1.0f / 200.0f);
			target.draw(pawnSprite, states);

            sf::RectangleShape rect(sf::Vector2f(0.5, 0.05));
            rect.setPosition(convert<sf::Vector2f>(pawn->getPosition() + glm::vec2(-0.25, -0.6)));

            rect.setFillColor(sf::Color::Red);
            target.draw(rect);

            float health = pawn->getHealth() / pawn->getInitialHealth();

            rect.setSize(sf::Vector2f(0.5f * health, 0.05f));
            rect.setFillColor(sf::Color::Green);
            target.draw(rect);
		}

		{
			sf::CircleShape shape(0.05, 12);
			shape.setFillColor(sf::Color::Black);

			auto &bullets = gameWorld->getBullets();
			for (auto bullet : bullets) {
				if (!bullet->getIsActive()) {
                    continue;
                }
				sf::RenderStates states;
				states.transform = bullet->getSFTransform();
				target.draw(shape, states);
			}
		}
	}

	glm::vec2 GameRenderer::screenToWorldPosition(glm::vec2 screenPos) {

		glm::vec2 screenPosInMeters = screenPos / dotsPerGameMeter;
		glm::vec2 center = glm::vec2(lastUsedView.getCenter().x, lastUsedView.getCenter().y);
		glm::vec2 size = glm::vec2(lastUsedView.getSize().x, lastUsedView.getSize().y);
		return screenPosInMeters - (size / 2.0f) + center;
	}

	void GameRenderer::setupView(sf::RenderTarget& target) {
		sf::Vector2u targetSize = target.getSize();
		glm::vec2 targetSizeInMeters = glm::vec2(targetSize.x, targetSize.y) / dotsPerGameMeter;

		sf::View view;
		view.setSize(targetSizeInMeters.x, targetSizeInMeters.y);
		view.setCenter(cameraTarget.x, cameraTarget.y);
		target.setView(view);

		lastUsedView = view;
	}

}