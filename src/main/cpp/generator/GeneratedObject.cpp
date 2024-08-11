#include "GeneratedObject.h"

namespace Quasigroup {

    GeneratedObject::GeneratedObject(unsigned long long int seed) {
        if (seed == 0) {
            seed = rd();
        }

        this->seed = seed;
        this->mersenne = std::mt19937(seed);
    }

    unsigned long long int GeneratedObject::getSeed() const {
        return seed;
    }

}