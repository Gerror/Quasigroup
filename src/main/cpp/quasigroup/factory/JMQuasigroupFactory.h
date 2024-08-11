#ifndef QUASIGROUP_JMQUASIGROUPFACTORY_H
#define QUASIGROUP_JMQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroupFactory.h"
#include "JMQuasigroup.h"

namespace Quasigroup {

    class JMQuasigroupFactory : public LatinSquareQuasigroupFactory {
    public:
        explicit JMQuasigroupFactory(int order) : LatinSquareQuasigroupFactory(order) {};
        JMQuasigroup* create() override;
    };

}

#endif //QUASIGROUP_JMQUASIGROUPFACTORY_H
