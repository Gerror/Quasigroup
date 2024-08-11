#include "FNQuasigroupFactory.h"

namespace Quasigroup {

    FNQuasigroup* FNQuasigroupFactory::create() {
        return new FNQuasigroup(k, inverseOperations);
    }

}
