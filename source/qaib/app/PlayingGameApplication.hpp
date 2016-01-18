#pragma once

#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>

#include <memory>

namespace qaib {

	class PlayingGameApplication: public Application {
	private:
		GameWorld gameWorld;
		GameRenderer gameRenderer;
		std::shared_ptr<Pawn> playerPawn;
	protected:
		virtual void doFrame(float deltaTime) override;
	public:
		PlayingGameApplication();
	};

}