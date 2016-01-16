#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/KeptInGameWorld.hpp>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable, public KeptInGameWorld {
	private:
		PawnController* controller;
		float moveSpeed;
	public:
		Pawn();

		void setController(PawnController* controller);	// takes own
		inline PawnController* getController() { return controller; } // borrow
		
		void applyPawnControl(float deltaTime);

		virtual ~Pawn();
	};

}