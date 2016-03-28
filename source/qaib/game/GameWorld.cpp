#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	GameWorld::GameWorld() : physicsWorld(b2Vec2_zero) {}

	Pawn& GameWorld::createPawn() {

		pawns.push_back(Pawn());

		Pawn& pawn = pawns.back();

		b2BodyDef pawnBodyDef;
		pawnBodyDef.type = b2_dynamicBody;
		pawnBodyDef.position = convert<b2Vec2>(pawn.getPosition());
		pawnBodyDef.angle = pawn.getRotation();

		auto body = physicsWorld.CreateBody(&pawnBodyDef);
		b2CircleShape pawnShape;
		pawnShape.m_radius = 0.35f;

		b2FixtureDef pawnFixtureDef;
		pawnFixtureDef.shape = &pawnShape;
		pawnFixtureDef.density = 1;
		body->CreateFixture(&pawnFixtureDef);

		pawn.setPhysicsBody(body);

		return pawn;
	}

	StaticObject& GameWorld::createStaticObject(StaticObjectClass &cl){

		statics.push_back(StaticObject(cl));

		StaticObject& obj = statics.back();



		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = convert<b2Vec2>(obj.getPosition());
		bodyDef.angle = obj.getRotation();

		auto body = physicsWorld.CreateBody(&bodyDef);
		auto shape = obj.getShape();
		b2FixtureDef fixtureDef;
		fixtureDef.shape = shape.get();
		fixtureDef.density = 1;
		body->CreateFixture(&fixtureDef);

		obj.setPhysicsBody(body);

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
		for (auto& pawn : pawns) {
			pawn.doTick(*this, deltaTime);
		}

		for (auto& object : statics) {
			object.getPhysicsBody()->SetTransform(convert<b2Vec2>(object.getPosition()), object.getPhysicsBody()->GetAngle());
		}

		physicsWorld.Step(deltaTime, 10, 10);

		for (auto& pawn : pawns) {
			pawn.setPosition(convert<glm::vec2>(pawn.getPhysicsBody()->GetPosition()));
		}
	}

	GameWorld::~GameWorld() {}

}