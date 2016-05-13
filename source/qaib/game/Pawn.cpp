#include <qaib/game/Pawn.hpp>

#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	Pawn::Pawn(b2Body* body) {
		moveSpeed = 5.0f;
		controller = nullptr;

		shootAllowed = true;
		lastShootTimer = 0;
		shootTimeout = 1;

		rotation = 0;

		physicsBody = body;

		b2CircleShape pawnShape;
		pawnShape.m_radius = 0.35f;

		b2FixtureDef pawnFixtureDef;
		pawnFixtureDef.shape = &pawnShape;
		pawnFixtureDef.density = 1;
		physicsBody->CreateFixture(&pawnFixtureDef);
	}

	void Pawn::doTick(GameWorld& gameWorld, float deltaTime) {
		using glm::vec2;
		using glm::normalize;

		if (!shootAllowed) {
			lastShootTimer += deltaTime;
			if (lastShootTimer > shootTimeout) {
				shootAllowed = true;
			}
		}

		if (controller == nullptr) {
			physicsBody->SetLinearVelocity(b2Vec2_zero);
			return;
		}
		auto movementDirection = controller->movementDirection() * moveSpeed;

		vec2 forward = controller->turningTo();
		float rotation = glm::orientedAngle(vec2(1, 0), normalize(forward));

		setRotation(rotation);

		if (controller->shouldAttack() && shootAllowed) {
			gameWorld.doShot(getPosition(), forward);
			lastShootTimer = 0;
			shootAllowed = false;
		}

		physicsBody->SetLinearVelocity(convert<b2Vec2>(movementDirection));
	}

	glm::vec2 Pawn::getPosition() const {
		return convert<glm::vec2>(physicsBody->GetPosition());
	}

	void Pawn::setPosition(const glm::vec2& pos) {
		physicsBody->SetTransform(convert<b2Vec2>(pos), 0);
	}

	float Pawn::getRotation() const {
		return rotation;
	}

	void Pawn::setRotation(float rot) {
		rotation = rot;
	}

	Pawn::~Pawn() {	}
}