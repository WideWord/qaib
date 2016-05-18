#pragma once

#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/app/ObjectClassManager.hpp>
#include <qaib/util/Typedef.hpp>

namespace qaib {

	class PlayingGameApplication: public Application {
	private:
		GameWorld gameWorld;
		GameRenderer gameRenderer;
		Ref<Pawn> playerPawn;
		ObjectClassManager objectClassManager;
	protected:
		virtual void init() override;
		virtual void doFrame(float deltaTime) override;
	public:
		PlayingGameApplication();
	};

}