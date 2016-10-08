#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <vector>
#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/game/Pawn.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace qaib {

    void NeuralNetworkPawnController::prepareTick(GameWorld& gameWorld, float deltaTime) {
        this->deltaTime = deltaTime;

        auto image = vision.drawFrame(gameWorld, *getPawn()).copyToImage();

        std::vector<float> inputs;
        auto size = image.getSize();
        for (int x = 0; x < size.x; ++x) {
            for (int y = 0; y < size.y; ++y) {
                auto pix = image.getPixel(x, y);
                inputs.push_back(((float)pix.r) / 127.0f - 1.0f);
                inputs.push_back(((float)pix.g) / 127.0f - 1.0f);
            }
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