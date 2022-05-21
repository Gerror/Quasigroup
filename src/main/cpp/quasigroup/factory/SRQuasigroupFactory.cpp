//
// Created by Gerror on 07.04.2022.
//

#include "SRQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *SRQuasigroupFactory::createQuasigroup(int k, int n) {
        return new SRQuasigroup(k, n);
    }

}
