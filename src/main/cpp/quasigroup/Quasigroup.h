//
// Created by Gerror on 04.03.2022.
//

#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <ostream>
#include <random>
#include <iostream>
#include <queue>
#include <ctime>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Unordered pair of elements required for primality test
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
        int getOrder() const;
        bool isAffine() const;
        bool isSimple() const;
        friend std::ostream &operator<<(std::ostream &out, const Quasigroup &q);
    protected:
        int order;
        Quasigroup() = default;
    };

}

#endif //QUASIGROUP_QUASIGROUP_H
