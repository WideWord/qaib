#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>


namespace qaib {

	PlayingGameApplication::PlayingGameApplication(const std::string& aiFilename) : gameWorld(20, 15) {
		ai = Population::load(aiFilename);
	}

	void PlayingGameApplication::init() {
		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = gameWorld.createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

        int aiPawnMax = 2;
        for (auto& net : ai->getNeuralNetworks()) {
            aiPawnMax -= 1;
            if (aiPawnMax == -1) break;
            auto pawn = gameWorld.createPawn();
            pawn->useController<NeuralNetworkPawnController>(net, playerPawn);
            pawn->setPosition(glm::vec2(Random::getFloat(-5, 5), Random::getFloat(-5, 5)));
            pawn->setRotation(Random::getFloat(-M_PI, M_PI));
        }
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
