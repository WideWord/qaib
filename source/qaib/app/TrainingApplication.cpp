#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>

namespace qaib {

    TrainingApplication::TrainingApplication() : population(50, 10 * 10 * 2 + 1, 4), aiVision(10, 10, 4) {

    }

    void TrainingApplication::init() {
        newPopulation();
    }

    void TrainingApplication::newPopulation() {
        if (gameWorld) {
            std::vector<float> fitness;
            for (auto& pawn : gameWorld->getPawns()) {
                auto score = pawn->getScore();
                if (score < 0.1f) {
                    score = 0.1f;
                }
                fitness.push_back(score / (pawn->getHealth() / 10.0f + 0.1f));
            }

            population.makeSelection(50, fitness);
        }

        gameWorld = Ref<GameWorld>(new GameWorld(50, 50));
        gameRenderer.setGameWorld(gameWorld.get());

        for (auto& net : population.getNeuralNetworks()) {
            auto pawn = gameWorld->createPawn();
            pawn->setPosition(glm::vec2(Random::getFloat(-30, 30), Random::getFloat(-30, 30)));
            pawn->useController<NeuralNetworkPawnController>(net, aiVision);
        }

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