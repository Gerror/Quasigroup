#include "SRQuasigroupFactory.h"

namespace Quasigroup {

    SRQuasigroup* SRQuasigroupFactory::create() {
        return new SRQuasigroup(k, n, inverseOperations);
    }

}
