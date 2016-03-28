#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/PawnController.hpp>

#include <memory>
#include <Box2D/Dynamics/b2Body.h>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable {
	private:
		PawnController* controller;
		float moveSpeed;

		b2Body* physicsBody;
	protected:
		friend class GameWorld;
		void setPhysicsBody(b2Body* body) {
			physicsBody = body;
		}
	public:
		Pawn();

		b2Body* getPhysicsBody() {
			return physicsBody;
		}

		template<typename C, typename ... Args> void useController(Args& ... args) {
			if (controller != nullptr) delete controller;
			controller = new C(args...);
			controller->setPawn(this);
		};

		void doTick(GameWorld& gameWorld, float deltaTime);

		virtual ~Pawn();
	};

}