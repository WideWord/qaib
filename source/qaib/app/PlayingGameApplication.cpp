#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticObject.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication(): playerPawn(gameWorld.createPawn()) {}

	void PlayingGameApplication::init() {
		objectClassManager.findClasses();

		gameRenderer.setGameWorld(&gameWorld);

		playerPawn.useController<PlayerPawnController>(gameRenderer, getMainTarget());

		auto pickupClass = objectClassManager.getStaticObjectClassWithName("veh_pickup");
		gameWorld.createStaticObject(*pickupClass).setPosition(glm::vec2(0, 0));

		auto anotherPawn = gameWorld.createPawn();
		anotherPawn.setPosition(glm::vec2(4, 4));
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);

		gameRenderer.setCameraTarget(playerPawn.getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}