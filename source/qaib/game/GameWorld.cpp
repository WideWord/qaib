#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <qaib/game/Bullet.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/ObstructionGenerator.hpp>
#include <qaib/util/Random.hpp>

namespace qaib {

	GameWorld::GameWorld(const Config& cfg) : physicsWorld(b2Vec2_zero) {
		physicsWorld.SetContactListener(this);
        physicsWorld.SetContactFilter(this);


        worldSize = cfg.size;

        buildFieldEdges();

        ObstructionGenerator generator(physicsWorld, obstructions);
        generator.generate(cfg.seed, cfg.obstructionCount, cfg.size);
	}

    void GameWorld::buildFieldEdges() {

        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;

        auto body = physicsWorld.CreateBody(&bodyDef);

        fieldEdges = body;

        b2PolygonShape shape;
        b2FixtureDef fixture;
        fixture.shape = &shape;

        for (int i = 0; i < 80; ++i) {
            b2Vec2 points[4];

            float angle = (float)i * (float)M_PI / 40.0f;
            float nextAngle = (float)(i + 1) * (float)M_PI / 40.0f;
            float radius = worldSize * 0.5f;

            points[0] = b2Vec2(sinf(angle) * radius, cosf(angle) * radius);
            points[1] = b2Vec2(sinf(nextAngle) * radius, cosf(nextAngle) * radius);
            points[2] = b2Vec2(sinf(nextAngle) * (radius + 1.0f), cosf(nextAngle) * (radius + 1.0f));
            points[3] = b2Vec2(sinf(angle) * (radius + 1.0f), cosf(angle) * (radius + 1.0f));

            shape.Set(points, 4);

            body->CreateFixture(&fixture);
        }
    }

	Ref<Pawn> GameWorld::createPawn() {

        using namespace glm;

		b2BodyDef pawnBodyDef;
		pawnBodyDef.type = b2_dynamicBody;

		auto body = physicsWorld.CreateBody(&pawnBodyDef);

		auto pawn = Ref<Pawn>(new Pawn(body));
		pawns.push_back(pawn);

        float angle = Random::getFloat(-M_PI, M_PI);
        float dist = Random::getFloat(0, worldSize * 0.5f - 0.5f);

        pawn->setPosition(rotate(vec2(0, 1), angle) * dist);

		return pawn;
	}

	void GameWorld::doShot(glm::vec2 fromPosition, glm::vec2 inDirection) {

        auto bullet = allocBullet();

		auto normalizedDirection = glm::normalize(inDirection);

        bullet->setPosition(fromPosition + normalizedDirection * 0.5f);
        bullet->setRotation(glm::orientedAngle(glm::vec2(1, 0), normalizedDirection));

		bullet->getPhysicsBody()->SetLinearVelocity(convert<b2Vec2>(normalizedDirection * 10.0f));


        bullet->shootBy = currentShootBy;
    }

	void GameWorld::BeginContact(b2Contact* contact) {
		Movable* a = (Movable*)contact->GetFixtureA()->GetBody()->GetUserData();
		Movable* b = (Movable*)contact->GetFixtureB()->GetBody()->GetUserData();

		Bullet* ba = dynamic_cast<Bullet*>(a);
		Bullet* bb = dynamic_cast<Bullet*>(b);

		Damagable* da = dynamic_cast<Damagable*>(a);
		Damagable* db = dynamic_cast<Damagable*>(b);

		if (ba && db) {
            if (ba->isActive) {
                db->applyDamage(20);
                if (ba->shootBy && ba->shootBy.get() != db) {
                    ba->shootBy->addScore(1);
                }
            }
		} else if (bb && da) {
            if (bb->isActive) {
                da->applyDamage(20);
                if (bb->shootBy && bb->shootBy.get() != da) {
                    bb->shootBy->addScore(1);
                }
            }
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

        if (ba && bb) {
            return false;
        }

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
                currentShootBy = pawn;
				pawn->doTick(*this, deltaTime);
                currentShootBy = nullptr;
            }

			it = nextIt;
		}

		physicsWorld.Step(deltaTime, 10, 10);
	}

    float GameWorld::rayCast(glm::vec2 fromPosition, glm::vec2 inDirection) {
        raycastFraction = 1;
        physicsWorld.RayCast(this, convert<b2Vec2>(fromPosition), convert<b2Vec2>(fromPosition + glm::normalize(inDirection) * 100.0f));
        return raycastFraction * 100.0f;
    }

    float GameWorld::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
        if (fixture->GetBody()->GetType() != b2_staticBody) return raycastFraction;
        raycastFraction = fraction;
        return fraction;
    }

    GameWorld::~GameWorld() {

	}

}
