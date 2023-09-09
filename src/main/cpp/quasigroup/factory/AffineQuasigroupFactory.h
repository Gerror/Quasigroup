#ifndef QUASIGROUP_AFFINEQUASIGROUPFACTORY_H
#define QUASIGROUP_AFFINEQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"
#include "AffineQuasigroup.h"
#include "LatinSquareQuasigroupFactory.h"

namespace Quasigroup {

    class AffineQuasigroupFactory : public LatinSquareQuasigroupFactory {
    public:
        LatinSquareQuasigroup *createQuasigroup(int order) override;
    };

}

#endif //QUASIGROUP_AFFINEQUASIGROUPFACTORY_H
