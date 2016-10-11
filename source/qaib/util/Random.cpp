#include <qaib/util/Random.hpp>
#include <time.h>

std::default_random_engine qaib::Random::generator(time(NULL));
