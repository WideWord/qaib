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
        Ref<Pawn> enemy;

        std::vector<float> outputs;
        float deltaTime;
    public:
        inline NeuralNetworkPawnController(const Ref<NeuralNetwork>& net, const Ref<Pawn>& enemy)
        : net(net), enemy(enemy) {}

        void prepareTick(GameWorld& gameWorld, float deltaTime) override;
        glm::vec2 movementDirection() override;
        glm::vec2 turningTo() override;
        bool shouldAttack() override;

        static const int inputsCount = 7;
        static const int outputsCount = 4;
    };

}