#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/KeptInGameWorld.hpp>

#include <memory>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable, public KeptInGameWorld {
	private:
		std::shared_ptr<PawnController> controller;
		float moveSpeed;
	public:
		Pawn();

		void setController(std::shared_ptr<PawnController> controller);
		inline std::shared_ptr<PawnController> getController() { return controller; }
		
		void applyPawnControl(float deltaTime);

		virtual ~Pawn();
	};

}