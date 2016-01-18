#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>


namespace qaib {

	class Pawn;
	class StaticObject;

	class GameWorld {
	private:
		struct PawnEntry {
			std::shared_ptr<Pawn> pawn;
			b2Body* body;
		};

		std::list<PawnEntry> pawnEntries;

		std::list<std::shared_ptr<Pawn>> pawns;

		struct StaticObjectEntry {
			std::shared_ptr<StaticObject> object;
			b2Body* body;
		};

		std::list<StaticObjectEntry> staticObjectEntries;

		std::list<std::shared_ptr<StaticObject>> statics;

		b2World physicsWorld;
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