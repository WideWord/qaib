#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticObject.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() : gameWorld(50, 50) {}

	void PlayingGameApplication::init() {
		objectClassManager.findClasses();

		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = gameWorld.createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

		pickup->setPosition(glm::vec2(0, 0));
		pickup->setRotation(0);

		auto anotherPawn = gameWorld.createPawn();
		anotherPawn->setPosition(glm::vec2(4, 4));
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);

		if (playerPawn->isDead()) {
			quit();
		}

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}