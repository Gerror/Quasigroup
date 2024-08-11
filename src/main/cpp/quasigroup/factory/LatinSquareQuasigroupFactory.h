#ifndef QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H
#define QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"
#include "QuasigroupFactory.h"

namespace Quasigroup {

    class LatinSquareQuasigroupFactory : public QuasigroupFactory {
    protected:
        int order;
    public:
        LatinSquareQuasigroupFactory(int order): order{order} {}
        virtual LatinSquareQuasigroup* create() override = 0;
        int getOrder() override { return order; };
    };

}

#endif //QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H
