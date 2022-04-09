//
// Created by Gerror on 07.04.2022.
//

#include "PFQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *PFQuasigroupFactory::createQuasigroup(int k, int n) {
        return new PFQuasigroup(k, n);
    }

}
