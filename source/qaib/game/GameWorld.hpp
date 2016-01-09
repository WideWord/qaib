#pragma once

#include <list>
#include <Box2D/Box2D.h>

namespace qaib {

	class Pawn;

	class GameWorld {
	private:
		std::list<Pawn*> _pawns;
		//b2World world;
	public:
		GameWorld();

		void addPawn(Pawn* pawn); // takes own
		inline const std::list<Pawn*>& pawns() { return _pawns; }

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}