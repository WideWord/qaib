#include <qaib/gfx/GameRenderer.hpp>

#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/game/Bullet.hpp>

namespace qaib {
	
	GameRenderer::GameRenderer() {
		pawnTexture.loadFromFile("data/kek.png");
		pawnSprite.setTexture(pawnTexture);
		pawnSprite.setOrigin(103.5f, 103.5f);

		sandTexture.loadFromFile("data/art/terrain/sand.jpg");
		sandTexture.setRepeated(true);

        rockTexture.loadFromFile("data/art/terrain/rock.jpg");
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
            sand.setTextureRect(sf::IntRect(0, 0, 256 * 50, 256 * 50));

            target.draw(sand);
        }

		auto& staticObjects = gameWorld->getStaticObjects();
		for (auto object : staticObjects) {
			auto sprite = object->getSprite();
			if (sprite == nullptr) continue;
			sf::RenderStates states;
			states.transform = object->getSFTransform();
			target.draw(*sprite, states);
		}

		auto& pawns = gameWorld->getPawns();
		for (auto pawn : pawns) {
			sf::RenderStates states;
			states.transform = pawn->getSFTransform();
			states.transform = states.transform.scale(1.0f / 200.0f, 1.0f / 200.0f);
			target.draw(pawnSprite, states);
		}

		{
			sf::RectangleShape shape(sf::Vector2f(0.3, 0.02));
			shape.setFillColor(sf::Color::Yellow);

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