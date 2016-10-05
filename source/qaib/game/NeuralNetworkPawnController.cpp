#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <vector>
#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/game/Pawn.hpp>

namespace qaib {

    void NeuralNetworkPawnController::prepareTick(GameWorld& gameWorld, float deltaTime) {
        auto image = vision.drawFrame(gameWorld, *getPawn()).copyToImage();

        std::vector<float> inputs;
        auto size = image.getSize();
        for (int x = 0; x < size.x; ++x) {
            for (int y = 0; y < size.y; ++y) {
                auto pix = image.getPixel(x, y);
                inputs.push_back(((float)pix.r) / 127.0f - 1.0f);
                inputs.push_back(((float)pix.g) / 127.0f - 1.0f);
                inputs.push_back(((float)pix.b) / 127.0f - 1.0f);
            }
        }


        inputs.push_back(getPawn()->getHealth() / getPawn()->getInitialHealth());

        outputs = net->execute(inputs);
    }

    glm::vec2 NeuralNetworkPawnController::movementDirection() {
        return glm::vec2(outputs[0], outputs[1]);
    }

    glm::vec2 NeuralNetworkPawnController::turningTo() {
        return glm::vec2(outputs[2], outputs[3]);
    }

    bool NeuralNetworkPawnController::shouldAttack() {
        return outputs[4] > 0;
    }


}