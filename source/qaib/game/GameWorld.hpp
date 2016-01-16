#pragma once

#include <list>
#include <Box2D/Box2D.h>

namespace qaib {

	class Pawn;

	class GameWorld {
	private:
		std::list<Pawn*> pawns;
		//b2World world;
	public:
		GameWorld();

		void addPawn(Pawn* pawn); // takes own
		inline const std::list<Pawn*>& getPawns() { return pawns; }

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}