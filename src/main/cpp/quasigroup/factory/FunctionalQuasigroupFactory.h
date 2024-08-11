#ifndef QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H
#define QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H

#include "FunctionalQuasigroup.h"
#include "QuasigroupFactory.h"

namespace Quasigroup {

    class FunctionalQuasigroupFactory : public QuasigroupFactory {
    protected:
        int k;
        int n;
    public:
        FunctionalQuasigroupFactory(int k, int n): k(k), n(n) {};
        int getOrder() override { return pow(k, n); }
    };

}

#endif //QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H
