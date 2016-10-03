#include <qaib/app/TrainingApplication.hpp>

namespace qaib {

    TrainingApplication::TrainingApplication() : gameWorld(50, 50) {}

    void TrainingApplication::init() {
        gameRenderer.setGameWorld(&gameWorld);
    }

    void TrainingApplication::doFrame(float deltaTime) {
        gameWorld.doTick(deltaTime);

        gameRenderer.drawFrame(getMainTarget());
    }

}