//
// Created by Gerror on 07.04.2022.
//

#ifndef QUASIGROUP_PFQUASIGROUPFACTORY_H
#define QUASIGROUP_PFQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "PFQuasigroup.h"

namespace Quasigroup {

    class PFQuasigroupFactory : public FunctionalQuasigroupFactory {
    public:
        FunctionalQuasigroup *createQuasigroup(int k, int n) override;
    };

}

#endif //QUASIGROUP_PFQUASIGROUPFACTORY_H
