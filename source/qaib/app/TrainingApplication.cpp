#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>

namespace qaib {

    TrainingApplication::TrainingApplication() : population(10, 10 * 10 * 2 + 1, 5), aiVision(10, 10, 4) {

    }

    void TrainingApplication::init() {
        newPopulation();
    }

    void TrainingApplication::newPopulation() {
        gameWorld = Ref<GameWorld>(new GameWorld(50, 50));
        gameRenderer.setGameWorld(gameWorld.get());

        for (auto& net : population.getNeuralNetworks()) {
            auto pawn = gameWorld->createPawn();
            pawn->useController<NeuralNetworkPawnController>(net, aiVision);
        }
    }

    void TrainingApplication::doFrame(float deltaTime) {
        gameWorld->doTick(deltaTime);

        gameRenderer.drawFrame(getMainTarget());
    }

}