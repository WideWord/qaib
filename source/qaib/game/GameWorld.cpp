#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	GameWorld::GameWorld() : physicsWorld(b2Vec2_zero) {}

	Pawn* GameWorld::createPawn() {

		b2BodyDef pawnBodyDef;
		pawnBodyDef.type = b2_dynamicBody;

		auto body = physicsWorld.CreateBody(&pawnBodyDef);

		auto pawn = new Pawn(body);
		pawns.push_back(pawn);
		return pawn;
	}

	StaticObject* GameWorld::createStaticObject(StaticObjectClass &cl) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;

		auto body = physicsWorld.CreateBody(&bodyDef);

		auto obj = new StaticObject(cl, body);
		statics.push_back(obj);
		return obj;
	}

	void GameWorld::doShot(glm::vec2 fromPosition, glm::vec2 inDirection) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = convert<b2Vec2>(fromPosition);
		bodyDef.angle = 0;

		auto body = physicsWorld.CreateBody(&bodyDef);
		b2CircleShape shape;
		shape.m_radius = 0.05f;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1;
		body->CreateFixture(&fixtureDef);

		body->SetLinearVelocity(convert<b2Vec2>(glm::normalize(inDirection) * 10.0f));

		bullets.push_back(body);
	}

	void GameWorld::doTick(float deltaTime) {
		for (auto pawn : pawns) {
			pawn->doTick(*this, deltaTime);
		}

		physicsWorld.Step(deltaTime, 10, 10);

	}

	GameWorld::~GameWorld() {
		for (auto pawn : pawns) {
			delete pawn;
		}

		for (auto obj : statics) {
			delete obj;
		}

	}

}