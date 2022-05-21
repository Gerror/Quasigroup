//
// Created by Gerror on 06.04.2022.
//

#ifndef QUASIGROUP_FNQUASIGROUP_H
#define QUASIGROUP_FNQUASIGROUP_H

#include "FunctionalQuasigroup.h"
#include "FeistelNetwork.h"

namespace Quasigroup {

    /*
     * Квазигруппы на основе обобщенных сетей Фейстеля
     */

    class FNQuasigroup : public FunctionalQuasigroup  {
    public:
        int getProduct(int x, int y) const override;
        explicit FNQuasigroup(const FeistelNetwork& feistelNetwork);
        FNQuasigroup(int k, unsigned long long int seed = 0);
    };

}

#endif //QUASIGROUP_FNQUASIGROUP_H
