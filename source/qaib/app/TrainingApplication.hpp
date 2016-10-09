#pragma once


#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Population.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <vector>
#include <queue>

namespace qaib {

    class Pawn;

    class TrainingApplication: public Application {
    private:
        Ref<GameWorld> gameWorld;
        GameRenderer gameRenderer;
        Ref<Population> population;

        void newGeneration();
        void nextTest();

        std::queue<Ref<NeuralNetwork>> testQueue;
        std::vector<float> fitness;
        Ref<Pawn> aPawn, bPawn;

        float roundFrames;
        int generationCount;
    protected:
        virtual void init() override;
        virtual void doFrame(float deltaTime) override;
    public:
        TrainingApplication();
        TrainingApplication(int startFromGeneration);
    };

}