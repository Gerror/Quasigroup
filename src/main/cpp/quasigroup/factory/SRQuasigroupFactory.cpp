#include "SRQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *SRQuasigroupFactory::createQuasigroup(int k, int n) {
        return new SRQuasigroup(k, n, inverseOperations);
    }

    SRQuasigroupFactory::SRQuasigroupFactory(bool inverseOperations) {
        this->inverseOperations = inverseOperations;
    }

}
