#include <qaib/game/Pawn.hpp>

#include <qaib/game/PawnController.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

	Pawn::Pawn() {
		moveSpeed = 5.0f;
		controller = nullptr;
	}

	void Pawn::setController(std::shared_ptr<PawnController> newController) {
		controller = newController;
		controller->setPawn(this);
	}

	void Pawn::doTick(GameWorld& gameWorld, float deltaTime, glm::vec2& movementDirection) {
		using glm::vec2;
		using glm::normalize;

		if (controller == nullptr) return;
		movementDirection = controller->movementDirection() * moveSpeed;

		vec2 forward = controller->turningTo();
		float rotation = glm::orientedAngle(vec2(1, 0), normalize(forward));

		setRotation(rotation);

		if (controller->shouldAttack()) {
			gameWorld.doShot(getPosition(), getPosition());
		}
	}

	Pawn::~Pawn() { }
}