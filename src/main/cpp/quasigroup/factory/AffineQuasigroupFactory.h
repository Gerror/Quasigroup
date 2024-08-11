#ifndef QUASIGROUP_AFFINEQUASIGROUPFACTORY_H
#define QUASIGROUP_AFFINEQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"
#include "AffineQuasigroup.h"
#include "LatinSquareQuasigroupFactory.h"

namespace Quasigroup {

    class AffineQuasigroupFactory : public LatinSquareQuasigroupFactory {
    public:
        explicit AffineQuasigroupFactory(int order): LatinSquareQuasigroupFactory(order) {}
        LatinSquareQuasigroup* create() override;
    };

}

#endif //QUASIGROUP_AFFINEQUASIGROUPFACTORY_H
