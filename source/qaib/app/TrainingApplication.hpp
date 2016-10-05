#pragma once


#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Typedef.hpp>

namespace qaib {

    class TrainingApplication: public Application {
    private:
        GameWorld gameWorld;
        GameRenderer gameRenderer;
    protected:
        virtual void init() override;
        virtual void doFrame(float deltaTime) override;
    public:
        TrainingApplication();
    };

}