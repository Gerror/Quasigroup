//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_GENERATEDOBJECT_H
#define QUASIGROUP_GENERATEDOBJECT_H

#include <random>

namespace Quasigroup {

    class GeneratedObject {
    private:
        unsigned long long int seed;
        std::random_device rd;
    public:
        unsigned long long int getSeed() const;
    protected:
        std::mt19937 mersenne;
        virtual void generate() = 0;
        explicit GeneratedObject(unsigned long long int seed = 0);
    };

}

#endif //QUASIGROUP_GENERATEDOBJECT_H
