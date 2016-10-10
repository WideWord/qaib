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
        Ref<GameRenderer> gameRenderer;
        Ref<Population> population;

        void newGeneration();
        void nextTest();

        std::vector<float> fitness;
        Ref<Pawn> aPawn, bPawn;
        int aID, bID;

        float roundFrames;
        int generationCount;
        int generationRoundsCount;

        static const int populationSize = 30;
        static const int generationRoundsNum = 10;
        bool gui;
    protected:
        virtual void init() override;
        virtual void doFrame(float deltaTime) override;
    public:
        TrainingApplication(int startFromGeneration = -1, bool gui = true);
    };
}