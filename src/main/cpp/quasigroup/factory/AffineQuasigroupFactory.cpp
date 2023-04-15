#include "AffineQuasigroupFactory.h"

namespace Quasigroup {

    LatinSquareQuasigroup *AffineQuasigroupFactory::createQuasigroup(int order) {
        return new AffineQuasigroup(order);
    }

}