#pragma once

#include <qaib/game/GameObject.hpp>

namespace qaib {
	
	class PawnController;

	class Pawn : GameObject {
	private:
		PawnController* _controller;
	public:
		void setController(PawnController* controller);	// takes own
		inline PawnController* controller() { return _controller; } // borrow

		virtual ~Pawn();
	};

}