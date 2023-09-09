#ifndef QUASIGROUP_FNQUASIGROUPFACTORY_H
#define QUASIGROUP_FNQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "FNQuasigroup.h"

namespace Quasigroup {

    class FNQuasigroupFactory : public FunctionalQuasigroupFactory {
    private:
        bool inverseOperations;
    public:
        FNQuasigroupFactory(bool inverseOperations = false);
        FunctionalQuasigroup *createQuasigroup(int k, int n = 2) override;
    };

}

#endif //QUASIGROUP_FNQUASIGROUPFACTORY_H
