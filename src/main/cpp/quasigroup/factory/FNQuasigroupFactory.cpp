#include "FNQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *FNQuasigroupFactory::createQuasigroup(int k, int n) {
        return new FNQuasigroup(k, inverseOperations);
    }

    FNQuasigroupFactory::FNQuasigroupFactory(bool inverseOperations) {
        this->inverseOperations = inverseOperations;
    }

}
