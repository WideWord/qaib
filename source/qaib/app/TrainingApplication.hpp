#pragma once


#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Population.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>

namespace qaib {

    class TrainingApplication: public Application {
    private:
        Ref<GameWorld> gameWorld;
        GameRenderer gameRenderer;
        Population population;
        AIVisionGameRenderer aiVision;

        void newPopulation();
        float roundFrames;
    protected:
        virtual void init() override;
        virtual void doFrame(float deltaTime) override;
    public:
        TrainingApplication();
    };

}