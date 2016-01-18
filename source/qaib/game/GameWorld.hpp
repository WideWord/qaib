#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>

namespace qaib {

	class Pawn;
	class StaticObject;

	class GameWorld {
	private:
		std::list<std::shared_ptr<Pawn>> pawns;
		std::list<std::shared_ptr<StaticObject>> statics;
		//b2World world;
	public:
		GameWorld();

		void addPawn(std::shared_ptr<Pawn> pawn);
		inline const std::list<std::shared_ptr<Pawn>>& getPawns() { return pawns; }

		void addStaticObject(std::shared_ptr<StaticObject> object); // takes own
		inline const std::list<std::shared_ptr<StaticObject>>& getStaticObjects() { return statics; }

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}