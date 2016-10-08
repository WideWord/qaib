#pragma once

#include <list>
#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <qaib/util/Typedef.hpp>

namespace qaib {

	class Pawn;
	class StaticObject;
	class Bullet;
    class Obstruction;

	class GameWorld : private b2ContactListener, private b2ContactFilter {
	private:

		std::list<Ref<Pawn>> pawns;

		std::list<Ref<Bullet>> bullets;

        std::list<Ref<Obstruction>> obstructions;

        Ref<Bullet> allocBullet();
        void freeBullet(Ref<Bullet> bullet);
        void freeBullet(Bullet* bullet);

		b2World physicsWorld;

		virtual void BeginContact(b2Contact* contact) override;
        virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

        float worldSize;

        void buildFieldEdges();

		Ref<Pawn> currentShootBy;

	public:
		GameWorld(float size, int obstructionCount);

        Ref<Pawn> createPawn();
		inline const std::list<Ref<Pawn>>& getPawns() { return pawns; }

		inline const std::list<Ref<Bullet>>& getBullets() { return bullets; }

        inline const std::list<Ref<Obstruction>>& getObstructions() { return obstructions; }

        inline const float getWorldSize() { return worldSize; }

		void doShot(glm::vec2 fromPosition, glm::vec2 inDirection);

		void doTick(float deltaTime);

		virtual ~GameWorld();
	};

}