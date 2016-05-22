#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <qaib/game/Bullet.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/ObstructionGenerator.hpp>

namespace qaib {

	GameWorld::GameWorld(float size, int obstructionCount) : physicsWorld(b2Vec2_zero) {
		physicsWorld.SetContactListener(this);
        physicsWorld.SetContactFilter(this);

        ObstructionGenerator generator(physicsWorld, obstructions);
        generator.generate(obstructionCount, size);
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

        auto bullet = allocBullet();

		auto normalizedDirection = glm::normalize(inDirection);

        bullet->setPosition(fromPosition + normalizedDirection * 0.5f);
        bullet->setRotation(glm::orientedAngle(glm::vec2(1, 0), normalizedDirection));

		bullet->getPhysicsBody()->SetLinearVelocity(convert<b2Vec2>(normalizedDirection * 10.0f));
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
            freeBullet(ba);
		}
		if (bb) {
            freeBullet(bb);
		}
	}

    bool GameWorld::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {
        Movable* a = (Movable*)fixtureA->GetBody()->GetUserData();
        Movable* b = (Movable*)fixtureA->GetBody()->GetUserData();

        Bullet* ba = dynamic_cast<Bullet*>(a);
        Bullet* bb = dynamic_cast<Bullet*>(b);

        if (ba) {
            if (!ba->isActive) {
                return false;
            }
        }

        if (bb) {
            if (!bb->isActive) {
                return false;
            }
        }

        return true;
    }


    Ref<Bullet> GameWorld::allocBullet() {
        for (auto bullet : bullets) {
            if (!bullet->isActive) {
                bullet->isActive = true;
                return bullet;
            }
        }

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        auto body = physicsWorld.CreateBody(&bodyDef);

        auto bullet = Ref<Bullet>(new Bullet(body));
        bullet->isActive = true;
        bullets.push_back(bullet);

        return bullet;
	}

	void GameWorld::freeBullet(Ref<Bullet> bullet) {
        freeBullet(bullet.get());
    }

    void GameWorld::freeBullet(Bullet* bullet) {
        bullet->isActive = false;
        bullet->getPhysicsBody()->SetLinearVelocity(b2Vec2_zero);
        bullet->getPhysicsBody()->SetAngularVelocity(0);
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

	}

}