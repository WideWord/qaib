#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticObject.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() {}

	void PlayingGameApplication::init() {
		objectClassManager.findClasses();

		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = gameWorld.createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

		auto pickupClass = objectClassManager.getStaticObjectClassWithName("veh_pickup");
		auto pickup = gameWorld.createStaticObject(*pickupClass);

		pickup->setPosition(glm::vec2(0, 0));
		pickup->setRotation(0);

		auto anotherPawn = gameWorld.createPawn();
		anotherPawn->setPosition(glm::vec2(4, 4));
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}