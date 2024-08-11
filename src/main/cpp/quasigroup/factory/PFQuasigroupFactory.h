#ifndef QUASIGROUP_PFQUASIGROUPFACTORY_H
#define QUASIGROUP_PFQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "PFQuasigroup.h"

namespace Quasigroup {

    class PFQuasigroupFactory : public FunctionalQuasigroupFactory {
    public:
        PFQuasigroupFactory(int k, int n) : FunctionalQuasigroupFactory(k, n) {}
        PFQuasigroup* create() override;
    };

}

#endif //QUASIGROUP_PFQUASIGROUPFACTORY_H
