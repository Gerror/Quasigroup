#ifndef QUASIGROUP_FNQUASIGROUPFACTORY_H
#define QUASIGROUP_FNQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "FNQuasigroup.h"

namespace Quasigroup {

    class FNQuasigroupFactory : public FunctionalQuasigroupFactory {
    private:
        bool inverseOperations;
    public:
        explicit FNQuasigroupFactory(int k, bool inverseOperations = false): inverseOperations(inverseOperations), FunctionalQuasigroupFactory(k, 2) {};
        FNQuasigroup* create() override;
    };

}

#endif //QUASIGROUP_FNQUASIGROUPFACTORY_H
