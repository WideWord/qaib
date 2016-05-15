#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "StaticObject.hpp"

namespace qaib {

	class Pawn;
	class StaticObject;
	class Bullet;

	class GameWorld : private b2ContactListener {
	private:

		std::list<Pawn*> pawns;

		std::list<StaticObject*> statics;

		std::list<Bullet*> bullets;

		b2World physicsWorld;

		virtual void BeginContact(b2Contact* contact) override;

		void removeBullet(Bullet* bullet);
	public:
		GameWorld();

		Pawn* createPawn();
		inline const std::list<Pawn*>& getPawns() { return pawns; }

		StaticObject* createStaticObject(StaticObjectClass& cl);
		inline const std::list<StaticObject*>& getStaticObjects() { return statics; }

		inline const std::list<Bullet*>& getBullets() { return bullets; }

		void doShot(glm::vec2 fromPosition, glm::vec2 inDirection);

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}