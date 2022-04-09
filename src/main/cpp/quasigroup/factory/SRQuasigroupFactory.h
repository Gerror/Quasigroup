//
// Created by Gerror on 07.04.2022.
//

#ifndef QUASIGROUP_SRQUASIGROUPFACTORY_H
#define QUASIGROUP_SRQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "SRQuasigroup.h"

namespace Quasigroup {

    class SRQuasigroupFactory : public FunctionalQuasigroupFactory {
    public:
        FunctionalQuasigroup *createQuasigroup(int k, int n) override;
    };

}

#endif //QUASIGROUP_SRQUASIGROUPFACTORY_H
