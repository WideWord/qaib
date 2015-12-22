#include <qaib/game/Pawn.hpp>

namespace qaib {

	void Pawn::setController(PawnController* controller) {
		if (_controller != nullptr) delete _controller;
		_controller = controller;
	}

	Pawn::~Pawn() {
		if (_controller != nullptr) delete _controller;
	}
}