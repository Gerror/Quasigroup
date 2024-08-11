#ifndef QUASIGROUP_FNQUASIGROUP_H
#define QUASIGROUP_FNQUASIGROUP_H

#include "FunctionalQuasigroup.h"
#include "function/family/FeistelNetwork.h"

namespace Quasigroup {

    /*
     * Quasigroups based on generalized Feistel networks
     */

    class FNQuasigroup : public FunctionalQuasigroup  {
    private:
        bool inverseOperations;
    public:
        int getProduct(int x, int y) const override;
        explicit FNQuasigroup(const FeistelNetwork& feistelNetwork, bool inverseOperations = false);
        FNQuasigroup(int k, bool inverseOperations = false, unsigned long long int seed = 0);
    };

}

#endif //QUASIGROUP_FNQUASIGROUP_H
