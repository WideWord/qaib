#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticVehicle.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() {
		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = std::make_shared<Pawn>();
		gameWorld.addPawn(playerPawn);

		playerPawn->setController(std::make_shared<PlayerPawnController>(gameRenderer, getMainTarget()));

		gameWorld.addStaticObject(std::make_shared<StaticVehicle>());


		auto anotherPawn = std::make_shared<Pawn>();
		gameWorld.addPawn(anotherPawn);
		anotherPawn->setPosition(glm::vec2(4, 4));
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}