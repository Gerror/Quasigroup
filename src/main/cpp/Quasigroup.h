//
// Created by rzhig on 04.03.2022.
//

#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#define NEW_LINE "\n"
#define SEPARATOR " "

#include <ostream>
#include <random>
#include <iostream>
#include <queue>
#include <time.h>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Unordered pairs of elements needed for
     * primality testing
     */

    struct UnorderedPair {
        int firstElement;
        int secondElement;
    };

    /*
     * Abstract class of quasigroups
     */

    class Quasigroup {
    public:
        virtual int getProduct(int x, int y) const = 0;
        int getOrder() const { return order; }
        unsigned long long int getSeed() const { return seed; }
        bool isAffine();
        bool isSimple();
        std::ostream & putLatinSquare(std::ostream &out) const;
    protected:
        int order;
        unsigned long long int seed;
        std::mt19937 mersenne;

        virtual void generate() = 0;
        Quasigroup() {}
    };

}

#endif //QUASIGROUP_QUASIGROUP_H
