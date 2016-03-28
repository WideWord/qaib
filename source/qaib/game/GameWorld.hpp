#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "StaticObject.hpp"

namespace qaib {

	class Pawn;
	class StaticObject;

	class GameWorld {
	private:

		std::list<Pawn> pawns;

		std::list<StaticObject> statics;

		std::list<b2Body*> bullets;

		b2World physicsWorld;
	public:
		GameWorld();

		Pawn& createPawn();
		inline const std::list<Pawn>& getPawns() { return pawns; }

		StaticObject& createStaticObject(StaticObjectClass& cl);
		inline const std::list<StaticObject>& getStaticObjects() { return statics; }

		void doShot(glm::vec2 fromPosition, glm::vec2 inDirection);

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}