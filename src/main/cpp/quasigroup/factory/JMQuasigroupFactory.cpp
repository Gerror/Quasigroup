//
// Created by Gerror on 07.04.2022.
//

#include "JMQuasigroupFactory.h"

namespace Quasigroup {

    LatinSquareQuasigroup *JMQuasigroupFactory::createQuasigroup(int order) {
        return new JMQuasigroup(order);
    }

}