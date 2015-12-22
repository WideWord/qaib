#pragma once

#include <glm/vec2.hpp>

namespace qaib {

	class Pawn;

	class PawnController {
	private:
		Pawn* _pawn;
	public:
		PawnController(Pawn* pawn);

		inline Pawn* pawn() { return _pawn; }

		virtual glm::vec2 movementDirection() = 0;
		virtual float turningToAngle() = 0;

		virtual ~PawnController();
	};

}