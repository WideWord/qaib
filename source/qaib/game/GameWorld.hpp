#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

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

		std::list<b2Body*> bullets;

		b2World physicsWorld;
	public:
		GameWorld();

		void addPawn(std::shared_ptr<Pawn> pawn);
		inline const std::list<std::shared_ptr<Pawn>>& getPawns() { return pawns; }

		void addStaticObject(std::shared_ptr<StaticObject> object); // takes own
		inline const std::list<std::shared_ptr<StaticObject>>& getStaticObjects() { return statics; }

		void doShot(glm::vec2 fromPosition, glm::vec2 inDirection);

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}