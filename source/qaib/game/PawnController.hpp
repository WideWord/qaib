#pragma once

#include <glm/vec2.hpp>

namespace qaib {

	class Pawn;
	class GameWorld;

	class PawnController {
	private:
		Pawn* pawn;
	protected:
		friend class Pawn;
		inline void setPawn(Pawn* newPawn) {
			assert(pawn == nullptr);
			pawn = newPawn;
		}
	public:
		PawnController();

		inline Pawn* getPawn() { return pawn; }

		virtual void prepareTick(GameWorld& gameWorld, float deltaTime);
		virtual glm::vec2 movementDirection() = 0;
		virtual glm::vec2 turningTo() = 0;
		virtual bool shouldAttack() = 0;

		virtual ~PawnController();
	};

}