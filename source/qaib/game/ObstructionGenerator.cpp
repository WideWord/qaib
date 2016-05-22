#include <qaib/game/ObstructionGenerator.hpp>

namespace qaib {

    ObstructionGenerator::ObstructionGenerator(
            b2World& physicsWorld,
            std::list<Ref<Obstruction>>& obstructionStorage
    ) : physicsWorld(physicsWorld), obstructionStorage(obstructionStorage) { }

    void ObstructionGenerator::generate(int count, float fieldSize) {

    }
}