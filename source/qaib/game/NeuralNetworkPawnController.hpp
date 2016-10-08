#pragma once

#include <qaib/game/PawnController.hpp>
#include <qaib/util/Typedef.hpp>
#include <vector>

namespace qaib {

    class NeuralNetwork;
    class AIVisionGameRenderer;

    class NeuralNetworkPawnController: public PawnController {
    private:
        Ref<NeuralNetwork> net;
        AIVisionGameRenderer& vision;

        std::vector<float> outputs;
        float deltaTime;
    public:
        inline NeuralNetworkPawnController(const Ref<NeuralNetwork>& net, AIVisionGameRenderer& vision)
        : vision(vision), net(net) {}

        void prepareTick(GameWorld& gameWorld, float deltaTime) override;
        glm::vec2 movementDirection() override;
        glm::vec2 turningTo() override;
        bool shouldAttack() override;
    };

}