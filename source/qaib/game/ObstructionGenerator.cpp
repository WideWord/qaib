#include <qaib/game/ObstructionGenerator.hpp>
#include <qaib/game/Obstruction.hpp>
#include <random>


namespace qaib {

    ObstructionGenerator::ObstructionGenerator(
            b2World& physicsWorld,
            std::list<Ref<Obstruction>>& obstructionStorage
    ) : physicsWorld(physicsWorld), obstructionStorage(obstructionStorage) { }

    void ObstructionGenerator::generate(int count, float fieldSize) {

        auto radius = fieldSize * 0.5f;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> randomDistance(0, radius);
        std::uniform_real_distribution<float> randomAngle(0, (float)M_PI * 2.0f);

        for (int i = 0; i < count; ++i) {
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;

            auto body = physicsWorld.CreateBody(&bodyDef);


            auto obstruction = Ref<Obstruction>(new Obstruction(body));

            auto distance = randomDistance(mt);
            auto angle = randomAngle(mt);

            obstruction->setPosition(glm::vec2(sinf(angle) * distance, cosf(angle) * distance));

            obstructionStorage.push_back(obstruction);
        }

    }
}