#include <qaib/game/Pawn.hpp>

#include <qaib/game/PawnController.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	Pawn::Pawn() {
		moveSpeed = 5.0f;
		controller = nullptr;
	}

	void Pawn::doTick(GameWorld& gameWorld, float deltaTime) {
		using glm::vec2;
		using glm::normalize;

		if (controller == nullptr) {
			physicsBody->SetLinearVelocity(b2Vec2_zero);
			physicsBody->SetTransform(convert<b2Vec2>(getPosition()), physicsBody->GetAngle());
			return;
		}
		auto movementDirection = controller->movementDirection() * moveSpeed;

		vec2 forward = controller->turningTo();
		float rotation = glm::orientedAngle(vec2(1, 0), normalize(forward));

		setRotation(rotation);

		if (controller->shouldAttack()) {
			gameWorld.doShot(getPosition(), forward);
		}

		physicsBody->SetLinearVelocity(convert<b2Vec2>(movementDirection));
		physicsBody->SetTransform(convert<b2Vec2>(getPosition()), physicsBody->GetAngle());
	}

	Pawn::~Pawn() {
		if (controller != nullptr) {
			delete controller;
		}
	}
}