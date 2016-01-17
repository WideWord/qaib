#pragma once

#include <list>
#include <Box2D/Box2D.h>

namespace qaib {

	class Pawn;
	class StaticObject;

	class GameWorld {
	private:
		std::list<Pawn*> pawns;
		std::list<StaticObject*> statics;
		//b2World world;
	public:
		GameWorld();

		void addPawn(Pawn* pawn); // takes own
		inline const std::list<Pawn*>& getPawns() { return pawns; }

		void addStaticObject(StaticObject* object); // takes own
		inline const std::list<StaticObject*>& getStaticObjects() { return statics; }

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}