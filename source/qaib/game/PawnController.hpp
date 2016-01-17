#pragma once

#include <glm/vec2.hpp>

namespace qaib {

	class Pawn;

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

		virtual glm::vec2 movementDirection() = 0;
		virtual glm::vec2 turningTo() = 0;
		virtual bool shouldDropWeapon() = 0;
		virtual bool shouldTakeWeapon() = 0;
		virtual bool shouldAttack() = 0;

		virtual ~PawnController();
	};

}