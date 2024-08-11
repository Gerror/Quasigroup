#ifndef QUASIGROUP_SRQUASIGROUPFACTORY_H
#define QUASIGROUP_SRQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "SRQuasigroup.h"

namespace Quasigroup {

    class SRQuasigroupFactory : public FunctionalQuasigroupFactory {
    private:
        bool inverseOperations;
    public:
        explicit SRQuasigroupFactory(int k, bool inverseOperations = false): inverseOperations(inverseOperations), FunctionalQuasigroupFactory(k, n) {};
        SRQuasigroup* create() override;
    };

}

#endif //QUASIGROUP_SRQUASIGROUPFACTORY_H
