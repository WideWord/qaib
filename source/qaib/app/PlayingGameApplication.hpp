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
		Ref<GameWorld> gameWorld;
		GameRenderer gameRenderer;
		Ref<Pawn> playerPawn;
		Ref<Pawn> aiPawn;
		Ref<Population> ai;
		Ref<Population> aiSecond;
	protected:
		virtual void init() override;
		virtual void doFrame(float deltaTime) override;
	public:
		struct Config {
			GameWorld::Config world;
			bool useJIT = false;
			bool useAI = false;
			bool vsAI = false;
			std::string aiFilename;
			std::string aiFilenameVS;
		};

		PlayingGameApplication(const Config& cfg);

	private:
		Config config;
		void newPlayers();
	};

}