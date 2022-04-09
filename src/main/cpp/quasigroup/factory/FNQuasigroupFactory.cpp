//
// Created by Gerror on 07.04.2022.
//

#include "FNQuasigroupFactory.h"

namespace Quasigroup {

    FunctionalQuasigroup *FNQuasigroupFactory::createQuasigroup(int k, int n) {
        return new FNQuasigroup(k);
    }

}
