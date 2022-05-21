//
// Created by Gerror on 07.04.2022.
//

#ifndef QUASIGROUP_FNQUASIGROUPFACTORY_H
#define QUASIGROUP_FNQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "FNQuasigroup.h"

namespace Quasigroup {

    class FNQuasigroupFactory : public FunctionalQuasigroupFactory {
    public:
        FunctionalQuasigroup *createQuasigroup(int k, int n) override;
    };

}

#endif //QUASIGROUP_FNQUASIGROUPFACTORY_H
