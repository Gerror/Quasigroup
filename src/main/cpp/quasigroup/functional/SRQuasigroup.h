//
// Created by Gerror on 08.03.2022.
//

#ifndef QUASIGROUP_SRQUASIGROUP_H
#define QUASIGROUP_SRQUASIGROUP_H

#include "ShiftRegister.h"
#include "FunctionalQuasigroup.h"

namespace Quasigroup {

    /*
     * Квазигруппы, получаемые
     * из регистров сдвига
     */

    class SRQuasigroup : public FunctionalQuasigroup {
    public:
        int getProduct(int x, int y) const override;
        explicit SRQuasigroup(const ShiftRegister& shiftRegister);
        SRQuasigroup(int k, int n, unsigned long long int seed = 0);
    };

}


#endif //QUASIGROUP_SRQUASIGROUP_H
