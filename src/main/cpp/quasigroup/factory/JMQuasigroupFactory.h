//
// Created by Gerror on 07.04.2022.
//

#ifndef QUASIGROUP_JMQUASIGROUPFACTORY_H
#define QUASIGROUP_JMQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroupFactory.h"
#include "JMQuasigroup.h"

namespace Quasigroup {

    class JMQuasigroupFactory : public LatinSquareQuasigroupFactory {
    public:
        LatinSquareQuasigroup *createQuasigroup(int order) override;
    };

}

#endif //QUASIGROUP_JMQUASIGROUPFACTORY_H
