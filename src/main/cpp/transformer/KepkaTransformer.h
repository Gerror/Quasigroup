#ifndef QUASIGROUP_KEPKATRANSFORMER_H
#define QUASIGROUP_KEPKATRANSFORMER_H

#include <quasigroup/Quasigroup.h>
#include <quasigroup/square/LatinSquareQuasigroup.h>
#include <random>
#include <ranges>
#include <set>
#include <iostream>
#include <utils/Helper.h>

namespace Quasigroup {

    class KepkaTransformer {
    public:
        static Quasigroup *transform(Quasigroup *original);
    };

}


#endif //QUASIGROUP_KEPKATRANSFORMER_H
