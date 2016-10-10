#pragma once

#include <qaib/app/Application.hpp>
#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Population.hpp>

namespace qaib {

	class Population;

	class PlayingGameApplication: public Application {
	private:
		GameWorld gameWorld;
		GameRenderer gameRenderer;
		Ref<Pawn> playerPawn;
		Ref<Population> ai;
		bool useJIT;
	protected:
		virtual void init() override;
		virtual void doFrame(float deltaTime) override;
	public:
		PlayingGameApplication(const std::string& aiFilename, bool useJIT = false);
	};

}