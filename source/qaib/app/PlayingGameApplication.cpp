#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() : gameWorld(50, 50) {}

	void PlayingGameApplication::init() {
		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = gameWorld.createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

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