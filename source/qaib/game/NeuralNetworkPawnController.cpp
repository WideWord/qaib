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
        this->deltaTime = deltaTime;

        std::vector<float> inputs;

        Ref<Pawn> nearestVisiblePawn;
        float nearestDist = INFINITY;
        auto me = getPawn();
        for (auto& pawn : gameWorld.getPawns()) {
            if (pawn.get() == me) {
                continue;
            }
            glm::vec2 dir = pawn->getPosition() - me->getPosition();
            auto dist = dir.x * dir.x + dir.y * dir.y;
            if (dist < nearestDist) {
                nearestDist = dist;
                nearestVisiblePawn = pawn;
            }
        }

        if (nearestVisiblePawn) {
            glm::vec2 dir = nearestVisiblePawn->getPosition() - me->getPosition();
            glm::vec2 forward = me->getForward();

            inputs.push_back(1);
            inputs.push_back(sqrtf(nearestDist));
            auto angle = glm::orientedAngle(forward, dir);
            inputs.push_back(angle);
        } else {
            inputs.push_back(-1);
            inputs.push_back(0);
            inputs.push_back(0);
        }


        inputs.push_back(getPawn()->getHealth() / getPawn()->getInitialHealth());

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