#pragma once

#include <Box2D/Box2D.h>
#include <list>
#include <qaib/util/Typedef.hpp>

namespace qaib {

    class Obstruction;

    class ObstructionGenerator {
    private:
        b2World& physicsWorld;
        std::list<Ref<Obstruction>>& obstructionStorage;
    public:
        ObstructionGenerator(b2World& physicsWorld, std::list<Ref<Obstruction>>& obstructionStorage);

        void generate(unsigned seed, int count, float fieldSize);
    };

}