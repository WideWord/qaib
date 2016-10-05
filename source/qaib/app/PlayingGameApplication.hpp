#pragma once

#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>

namespace qaib {

	class PlayingGameApplication: public Application {
	private:
		GameWorld gameWorld;
		GameRenderer gameRenderer;
		Ref<Pawn> playerPawn;
		AIVisionGameRenderer aiVision;
	protected:
		virtual void init() override;
		virtual void doFrame(float deltaTime) override;
	public:
		PlayingGameApplication();
	};

}