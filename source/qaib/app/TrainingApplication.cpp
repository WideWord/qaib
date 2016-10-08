#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>
#include <fstream>
#include <sstream>

namespace qaib {

    TrainingApplication::TrainingApplication() : population(30, 4, 4) {
        generationCount = 0;
    }

    void TrainingApplication::init() {
        newPopulation();
    }

    void TrainingApplication::newPopulation() {

        generationCount += 1;

        if (gameWorld) {
            std::vector<float> fitness;
            for (auto& pawn : gameWorld->getPawns()) {
                auto score = pawn->getScore();
                if (score < 0.1f) {
                    score = 0.1f;
                }
                fitness.push_back(score / (pawn->getHealth() / 10.0f + 0.1f));
            }

            population.makeSelection(30, fitness);
        }

        gameWorld = Ref<GameWorld>(new GameWorld(10, 3));
        gameRenderer.setGameWorld(gameWorld.get());

        for (auto& net : population.getNeuralNetworks()) {
            auto pawn = gameWorld->createPawn();
            pawn->setPosition(glm::vec2(Random::getFloat(-5, 5), Random::getFloat(-5, 5)));
            pawn->useController<NeuralNetworkPawnController>(net);
        }

        sf::Packet packet;
        population.writeTo(packet);

        std::stringstream ss;
        ss << "populations/" << generationCount << ".pop";

        std::ofstream out(ss.str());
        out.write((const char*)packet.getData(), packet.getDataSize());

        roundFrames = 0;
    }

    void TrainingApplication::doFrame(float deltaTime) {
        gameWorld->doTick(1.0f / 30.0f);
        roundFrames += 1;

        if (roundFrames > 30 * 8) {
            newPopulation();
        }

        gameRenderer.drawFrame(getMainTarget());
    }

}