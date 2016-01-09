#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/KeptInGameWorld.hpp>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable, public KeptInGameWorld {
	private:
		PawnController* _controller;
	public:
		void setController(PawnController* controller);	// takes own
		inline PawnController* controller() { return _controller; } // borrow
		
		void applyPawnControl();

		virtual ~Pawn();
	};

}