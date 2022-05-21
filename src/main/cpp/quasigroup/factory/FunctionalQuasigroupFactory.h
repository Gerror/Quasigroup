//
// Created by Gerror on 07.04.2022.
//

#ifndef QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H
#define QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H

#include "FunctionalQuasigroup.h"

namespace Quasigroup {

    class FunctionalQuasigroupFactory {
    public:
        virtual FunctionalQuasigroup *createQuasigroup(int k, int n) = 0;
    };

}

#endif //QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H
