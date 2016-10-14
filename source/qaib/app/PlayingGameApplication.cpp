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

            if (config.vsAI) {
                aiSecond = Population::load(config.aiFilenameVS);
            }
        }

	}

	void PlayingGameApplication::init() {
        newPlayers();
	}

    void PlayingGameApplication::newPlayers() {

        gameWorld = Ref<GameWorld>(new GameWorld(config.world));

        gameRenderer.setGameWorld(gameWorld.get());

        playerPawn = gameWorld->createPawn();
        if (ai) {
            aiPawn = gameWorld->createPawn();
        }

        if (aiSecond) {
            auto genomes = aiSecond->getGenomes();
            auto &genome = genomes[Random::getInt(0, genomes.size() - 1)];

            Ref<NeuralNetwork> net;
            if (config.useJIT) {
                auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                net = Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet));
            } else {
                net = genome.buildNeuralNetwork();
            }
            playerPawn->useController<NeuralNetworkPawnController>(net, aiPawn);
        } else {
            playerPawn->useController<PlayerPawnController>(gameRenderer, getMainTarget());
        }

        if (ai) {
            auto genomes = ai->getGenomes();
            auto &genome = genomes[Random::getInt(0, genomes.size() - 1)];

            auto pawn = aiPawn;
            Ref<NeuralNetwork> net;
            if (config.useJIT) {
                auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                net = Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet));
            } else {
                net = genome.buildNeuralNetwork();
            }
            pawn->useController<NeuralNetworkPawnController>(net, playerPawn);
        }
    }

	void PlayingGameApplication::doFrame(float deltaTime) {
		gameWorld->doTick(deltaTime);

        gameRenderer.setCameraTarget(playerPawn->getPosition());

        gameRenderer.drawFrame(getMainTarget());

		if (!config.vsAI && playerPawn->isDead()) {
			quit();
		}

        if ((ai && aiPawn->isDead()) || (config.vsAI && playerPawn->isDead())) {
            newPlayers();
        }

	}
}
