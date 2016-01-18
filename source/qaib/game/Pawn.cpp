#include <qaib/game/Pawn.hpp>

#include <qaib/game/PawnController.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace qaib {

	Pawn::Pawn() {
		moveSpeed = 5.0f;
		controller = nullptr;
	}

	void Pawn::setController(std::shared_ptr<PawnController> newController) {
		controller = newController;
		controller->setPawn(this);
	}

	void Pawn::applyPawnControl(float deltaTime) {
		using glm::vec2;
		using glm::normalize;

		if (controller == nullptr) return;
		vec2 pos = getPosition();
		pos += controller->movementDirection() * deltaTime * moveSpeed;

		vec2 forward = controller->turningTo();
		float rotation = glm::orientedAngle(vec2(1, 0), normalize(forward));

		setPosition(pos);
		setRotation(rotation);
	}

	Pawn::~Pawn() { }
}