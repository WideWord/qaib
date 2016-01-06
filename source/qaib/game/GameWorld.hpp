#pragma once

#include <list>

namespace qaib {

	class Pawn;

	class GameWorld {
	private:
		std::list<Pawn*> pawns;
	public:
		
		void addPawn(Pawn* pawn); // takes own
		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}