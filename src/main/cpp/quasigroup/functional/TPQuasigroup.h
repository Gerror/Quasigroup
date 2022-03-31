//
// Created by rzhig on 08.03.2022.
//

#ifndef QUASIGROUP_TPQUASIGROUP_H
#define QUASIGROUP_TPQUASIGROUP_H

#include "TotalPermutation.h"
#include "FunctionalQuasigroup.h"

namespace Quasigroup {

    /*
     * Квазигруппы, получаемые
     * из подстановок с полным дифференциалом
     */

    class TPQuasigroup : public FunctionalQuasigroup {
    public:
        int getProduct(int x, int y) const override;
        explicit TPQuasigroup(const TotalPermutation& totalPermutation);
        TPQuasigroup(int k, int n, unsigned long long int seed = 0);
    };

}


#endif //QUASIGROUP_TPQUASIGROUP_H
