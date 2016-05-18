#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <qaib/game/Bullet.hpp>
#include <glm/gtx/vector_angle.hpp>


namespace qaib {

	GameWorld::GameWorld() : physicsWorld(b2Vec2_zero) {
		physicsWorld.SetContactListener(this);
	}

	Ref<Pawn> GameWorld::createPawn() {

		b2BodyDef pawnBodyDef;
		pawnBodyDef.type = b2_dynamicBody;

		auto body = physicsWorld.CreateBody(&pawnBodyDef);

		auto pawn = Ref<Pawn>(new Pawn(body));
		pawns.push_back(pawn);
		return pawn;
	}

	Ref<StaticObject> GameWorld::createStaticObject(StaticObjectClass &cl) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;

		auto body = physicsWorld.CreateBody(&bodyDef);

		auto obj = Ref<StaticObject>(new StaticObject(cl, body));
		statics.push_back(obj);
		return obj;
	}

	void GameWorld::doShot(glm::vec2 fromPosition, glm::vec2 inDirection) {

		auto normalizedDirection = glm::normalize(inDirection);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = convert<b2Vec2>(fromPosition + normalizedDirection * 0.5f);
		bodyDef.angle = glm::orientedAngle(glm::vec2(1, 0), normalizedDirection);

		auto body = physicsWorld.CreateBody(&bodyDef);
		body->SetLinearVelocity(convert<b2Vec2>(normalizedDirection * 10.0f));


		bullets.push_back(new Bullet(body));
	}

	void GameWorld::BeginContact(b2Contact* contact) {
		Movable* a = (Movable*)contact->GetFixtureA()->GetBody()->GetUserData();
		Movable* b = (Movable*)contact->GetFixtureB()->GetBody()->GetUserData();

		Bullet* ba = dynamic_cast<Bullet*>(a);
		Bullet* bb = dynamic_cast<Bullet*>(b);

		Damagable* da = dynamic_cast<Damagable*>(a);
		Damagable* db = dynamic_cast<Damagable*>(b);

		if (ba && db) {
			db->applyDamage(20);
		} else if (bb && da) {
			da->applyDamage(20);
		}

		if (ba) {
			removeBullet(ba);
		}
		if (bb) {
			removeBullet(bb);
		}
	}

	void GameWorld::removeBullet(Bullet *bullet) {
		bullets.remove(bullet);
		bullet->getPhysicsBody()->SetUserData(nullptr);
		physicsWorld.DestroyBody(bullet->getPhysicsBody());
		delete bullet;
	}


	void GameWorld::doTick(float deltaTime) {

		for (auto it = pawns.begin(); it != pawns.end();) {
			auto pawn = *it;

			auto nextIt = it;
			++nextIt;


			if (pawn->isDead()) {
				pawn->getPhysicsBody()->SetUserData(nullptr);
				physicsWorld.DestroyBody(pawn->getPhysicsBody());
				pawns.erase(it);
			} else {
				pawn->doTick(*this, deltaTime);
			}

			it = nextIt;
		}

		physicsWorld.Step(deltaTime, 10, 10);
	}

	GameWorld::~GameWorld() {
		for (auto bullet: bullets) {
			delete bullet;
		}

	}

}