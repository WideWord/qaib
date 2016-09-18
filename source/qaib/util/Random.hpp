#pragma once

#include <random>

namespace qaib {

    class Random {
    private:
        static std::default_random_engine generator;
    public:
        inline static int getInt(int min, int max) {
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(generator);
        }
        inline static bool getBool() {
            return getInt(0, 1) == 0;
        }
        inline static float getFloat(float min, float max) {
            std::uniform_real_distribution<float> d(min, max);
            return d(generator);
        }
    };

}