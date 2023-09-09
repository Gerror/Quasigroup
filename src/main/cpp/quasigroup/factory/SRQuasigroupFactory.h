#ifndef QUASIGROUP_SRQUASIGROUPFACTORY_H
#define QUASIGROUP_SRQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "SRQuasigroup.h"

namespace Quasigroup {

    class SRQuasigroupFactory : public FunctionalQuasigroupFactory {
    private:
        bool inverseOperations;
    public:
        SRQuasigroupFactory(bool inverseOperations = false);
        FunctionalQuasigroup *createQuasigroup(int k, int n) override;
    };

}

#endif //QUASIGROUP_SRQUASIGROUPFACTORY_H
