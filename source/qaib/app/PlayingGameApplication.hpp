#pragma once

#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

	class PlayingGameApplication: public Application {
	private:

		GameWorld gameWorld;
		GameRenderer gameRenderer;
	protected:
		virtual void doFrame() override;
	public:
		PlayingGameApplication();
	};

}