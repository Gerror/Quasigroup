#ifndef QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H
#define QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"

namespace Quasigroup {

    class LatinSquareQuasigroupFactory {
    public:
        virtual LatinSquareQuasigroup *createQuasigroup(int order) = 0;
    };

}

#endif //QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H
