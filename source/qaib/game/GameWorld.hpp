#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "StaticObject.hpp"
#include <qaib/util/Typedef.hpp>

namespace qaib {

	class Pawn;
	class StaticObject;
	class Bullet;

	class GameWorld : private b2ContactListener, private b2ContactFilter {
	private:

		std::list<Ref<Pawn>> pawns;

		std::list<Ref<StaticObject>> statics;

		std::list<Ref<Bullet>> bullets;

        Ref<Bullet> allocBullet();
        void freeBullet(Ref<Bullet> bullet);
        void freeBullet(Bullet* bullet);

		b2World physicsWorld;

		virtual void BeginContact(b2Contact* contact) override;
        virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

	public:
		GameWorld();

        Ref<Pawn> createPawn();
		inline const std::list<Ref<Pawn>>& getPawns() { return pawns; }

        Ref<StaticObject> createStaticObject(StaticObjectClass& cl);
		inline const std::list<Ref<StaticObject>>& getStaticObjects() { return statics; }

		inline const std::list<Ref<Bullet>>& getBullets() { return bullets; }

		void doShot(glm::vec2 fromPosition, glm::vec2 inDirection);

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}