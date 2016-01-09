#include <qaib/game/Pawn.hpp>
#include <qaib/game/PawnController.hpp>

namespace qaib {

	void Pawn::setController(PawnController* controller) {
		if (_controller != nullptr) delete _controller;
		_controller = controller;
	}

	void Pawn::applyPawnControl() {
		if (_controller == nullptr) return;
		glm::vec2 pos = getPosition();
		pos += _controller->movementDirection();
		setPosition(pos);
	}

	Pawn::~Pawn() {
		if (_controller != nullptr) delete _controller;
	}
}