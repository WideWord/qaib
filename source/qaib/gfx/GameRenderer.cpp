#include <qaib/gfx/GameRenderer.hpp>

#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>

namespace qaib {

	GameRenderer::GameRenderer() {
		pawnTexture.loadFromFile("data/kek.png");
		pawnSprite.setTexture(pawnTexture);
	}

	void GameRenderer::drawFrame(sf::RenderTarget* target) {

		target->clear();
		
		auto& pawns = gameWorld->pawns();
		for (auto pawn : pawns) {
			sf::RenderStates states;
			states.transform = pawn->getSFTransform();
			target->draw(pawnSprite, states);
		}

	}

}