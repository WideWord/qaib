#pragma once

#include <qaib/game/Movable.hpp>

#include <memory>

namespace qaib {
	
	class PawnController;
	class GameWorld;

	class Pawn: public Movable {
	private:
		std::shared_ptr<PawnController> controller;
		float moveSpeed;
	public:
		Pawn();

		void setController(std::shared_ptr<PawnController> controller);
		inline std::shared_ptr<PawnController> getController() { return controller; }
		
		void doTick(GameWorld& gameWorld, float deltaTime, glm::vec2& outMovementDirection);

		virtual ~Pawn();
	};

}