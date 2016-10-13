#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/util/Random.hpp>
#include <qaib/nn/JITNeuralNetwork.hpp>


namespace qaib {

	PlayingGameApplication::PlayingGameApplication(const Config& cfg) {
		config = cfg;
		if (config.useAI) {
			ai = Population::load(cfg.aiFilename);
			config.world = ai->getWorldConfig();
		}
		gameWorld = Ref<GameWorld>(new GameWorld(config.world));
	}

	void PlayingGameApplication::init() {
		gameRenderer.setGameWorld(gameWorld.get());

		playerPawn = gameWorld->createPawn();

		playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());

		if (ai) {
			auto genomes = ai->getGenomes();
			auto &genome = genomes[Random::getInt(0, genomes.size())];

            auto pawn = gameWorld->createPawn();
            Ref<NeuralNetwork> net;
            if (config.useJIT) {
                auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                net = Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet));
            } else {
                net = genome.buildNeuralNetwork();
            }
            pawn->useController<NeuralNetworkPawnController>(net, playerPawn);
            pawn->setPosition(glm::vec2(Random::getFloat(-5, 5), Random::getFloat(-5, 5)));
            pawn->setRotation(Random::getFloat(-M_PI, M_PI));

            aiPawn = pawn;
		}
	}

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld->doTick(deltaTime);


		if (playerPawn->isDead()) {
			quit();
		}

        if (ai && aiPawn->isDead()) {
            auto genomes = ai->getGenomes();
            auto &genome = genomes[Random::getInt(0, genomes.size())];

            auto pawn = gameWorld->createPawn();
            Ref<NeuralNetwork> net;
            if (config.useJIT) {
                auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                net = Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet));
            } else {
                net = genome.buildNeuralNetwork();
            }
            pawn->useController<NeuralNetworkPawnController>(net, playerPawn);
            pawn->setPosition(glm::vec2(Random::getFloat(-15, 15), Random::getFloat(-15, 15)));
            pawn->setRotation(Random::getFloat(-M_PI, M_PI));

            aiPawn = pawn;
        }

		gameRenderer.setCameraTarget(playerPawn->getPosition());

		gameRenderer.drawFrame(getMainTarget());
	}
}
