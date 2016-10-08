#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <qaib/nn/Genome.hpp>
#include <qaib/nn/NeuralNetwork.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() : gameWorld(50, 50), aiVision(10, 10, 4) {}

	void PlayingGameApplication::init() {
		gameRenderer.setGameWorld(&gameWorld);

		playerPawn = gameWorld.createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

		InnovationGenerator g;
		Genome genome(g, 10 * 10 * 2 + 1, 5);
		for (int i = 0; i < 200; ++i) genome.mutate(g);
		auto net = genome.buildNeuralNetwork();

		auto anotherPawn = gameWorld.createPawn();
		anotherPawn->setPosition(glm::vec2(4, 4));
		anotherPawn->useController<NeuralNetworkPawnController>(net);
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld.doTick(deltaTime);


		if (playerPawn->isDead()) {
			quit();
		}

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());

		auto& texture = aiVision.drawFrame(gameWorld, *(playerPawn.get()));

		sf::Sprite sprite(texture);
		sprite.setScale(0.3f, 0.3f);
		sprite.setPosition(convert<sf::Vector2f>(playerPawn->getPosition() + glm::vec2(0, 1)));
		getMainTarget().draw(sprite);

	}
}