#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticVehicle.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() {
		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = new Pawn();
		gameWorld.addPawn(playerPawn);

		playerPawn->setController(new PlayerPawnController(gameRenderer, getMainTarget()));

		gameWorld.addStaticObject(new StaticVehicle());
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}