#include "AffineQuasigroupFactory.h"

namespace Quasigroup {

    LatinSquareQuasigroup* AffineQuasigroupFactory::create() {
        return new AffineQuasigroup(order);
    }

}