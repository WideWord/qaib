#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	GameWorld::GameWorld() : physicsWorld(b2Vec2_zero) {}

	void GameWorld::addPawn(std::shared_ptr<Pawn> pawn) {

		PawnEntry entry;

		entry.pawn = pawn;

		b2BodyDef pawnBodyDef;
		pawnBodyDef.type = b2_dynamicBody;
		pawnBodyDef.position = convert<b2Vec2>(pawn->getPosition());
		pawnBodyDef.angle = pawn->getRotation();

		entry.body = physicsWorld.CreateBody(&pawnBodyDef);
		b2CircleShape pawnShape;
		pawnShape.m_radius = 0.35f;

		b2FixtureDef pawnFixtureDef;
		pawnFixtureDef.shape = &pawnShape;
		pawnFixtureDef.density = 1;
		entry.body->CreateFixture(&pawnFixtureDef);

		pawnEntries.push_back(entry);

		pawns.push_back(pawn);
		pawn->movedToGameWorld(this);
	}

	void GameWorld::addStaticObject(std::shared_ptr<StaticObject> obj) {
		statics.push_back(obj);
		obj->movedToGameWorld(this);
	}


	void GameWorld::doTick(float deltaTime) {
		for (auto& entry : pawnEntries) {

			glm::vec2 movementDirection;

			entry.pawn->applyPawnControl(deltaTime, movementDirection);

			entry.body->SetLinearVelocity(convert<b2Vec2>(movementDirection));
			entry.body->SetTransform(convert<b2Vec2>(entry.pawn->getPosition()), entry.body->GetAngle());
		}

		physicsWorld.Step(deltaTime, 10, 10);

		for (auto& entry : pawnEntries) {
			entry.pawn->setPosition(convert<glm::vec2>(entry.body->GetPosition()));
		}
	}

	GameWorld::~GameWorld() {}

}