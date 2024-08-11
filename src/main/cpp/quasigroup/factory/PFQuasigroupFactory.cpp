#include "PFQuasigroupFactory.h"

namespace Quasigroup {

    PFQuasigroup* PFQuasigroupFactory::create() {
        return new PFQuasigroup(k, n);
    }

}
