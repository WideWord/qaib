#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <vector>
#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/game/Pawn.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

    void NeuralNetworkPawnController::prepareTick(GameWorld& gameWorld, float deltaTime) {
        using namespace glm;

        this->deltaTime = deltaTime;

        std::vector<float> inputs;

        auto me = getPawn();
        if (enemy && !enemy->isDead()) {
            vec2 dir = enemy->getPosition() - me->getPosition();
            vec2 forward = me->getForward();

            float dist = sqrtf((dir.x * dir.x + dir.y * dir.y)) / 50.0f;
            if (dist > 1.0f) dist = 1.0f;

            inputs.push_back(dist);

            dir = normalize(dir);
            auto angle = ((forward.x * dir.x + forward.y * dir.y) * 0.5f + 1);
            if (orientedAngle(forward, dir) < 0) angle = -angle;
            inputs.push_back(angle);
        } else {
            inputs.push_back(0);
            inputs.push_back(0);
        }

        inputs.push_back(me->getHealth() / me->getInitialHealth());

        auto img = vision.drawFrame(gameWorld, *getPawn()).copyToImage();
        auto size = img.getSize();
        for (int x = 0; x < size.x; ++x) {
            for (int y = 0; y < size.y; ++y) {
                inputs.push_back(((float)img.getPixel(x, y).r) / 255.0f);
            }
        }

        outputs = net->execute(inputs);
    }

    glm::vec2 NeuralNetworkPawnController::movementDirection() {
        return glm::rotate(glm::vec2(outputs[0], outputs[1]), -(getPawn()->getRotation()));
    }

    glm::vec2 NeuralNetworkPawnController::turningTo() {
        return glm::rotate(glm::vec2(1, 0), getPawn()->getRotation() + outputs[2] * deltaTime);

    }

    bool NeuralNetworkPawnController::shouldAttack() {
        return outputs[3] > 0;
    }


}