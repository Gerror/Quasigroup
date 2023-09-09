#include "PFQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *PFQuasigroupFactory::createQuasigroup(int k, int n) {
        return new PFQuasigroup(k, n);
    }

}
