#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/PawnController.hpp>

#include <memory>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable {
	private:
		PawnController* controller;
		float moveSpeed;
	public:
		Pawn();

		template<typename C, typename ... Args> void useController(Args& ... args) {
			if (controller != nullptr) delete controller;
			controller = new C(args...);
			controller->setPawn(this);
		};

		void doTick(GameWorld& gameWorld, float deltaTime, glm::vec2& outMovementDirection);

		virtual ~Pawn();
	};

}