//
// Created by rzhig on 08.03.2022.
//

#ifndef QUASIGROUP_TPQUASIGROUP_H
#define QUASIGROUP_TPQUASIGROUP_H

#include "TotalPermutation.h"
#include "Quasigroup.h"

namespace Quasigroup {

    /*
     * Квазигруппы, получаемые
     * из подстановок с полным дифференциалом
     */

    class TPQuasigroup : public Quasigroup {
    private:
        int k;
        int n;
        TotalPermutation totalPermutation;
    public:
        int getProduct(int x, int y) const override;
        explicit TPQuasigroup(const TotalPermutation& totalPermutation, unsigned long long int seed = time(nullptr));
        TPQuasigroup(int k, int n, unsigned long long int seed = time(nullptr)) : TPQuasigroup(TotalPermutation(k, n), seed) {}
    protected:
        void generate() override;
    };

}


#endif //QUASIGROUP_TPQUASIGROUP_H
