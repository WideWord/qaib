#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/StaticObject.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() {
		objectClassManager.findClasses();

		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = std::make_shared<Pawn>();
		gameWorld.addPawn(playerPawn);

		playerPawn->setController(std::make_shared<PlayerPawnController>(gameRenderer, getMainTarget()));

		auto pickupClass = objectClassManager.getStaticObjectClassWithName("veh_pickup");
		auto pickup = std::make_shared<StaticObject>(pickupClass);
		gameWorld.addStaticObject(pickup);

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