#ifndef QUASIGROUP_AFFINEQUASIGROUP_H
#define QUASIGROUP_AFFINEQUASIGROUP_H

#include <vector>

#include "GeneratedObject.h"
#include "LatinSquareQuasigroup.h"

namespace Quasigroup {
    /*
     * Generates an affine quasigroup if the order is a prime number
     */

    class AffineQuasigroup : public LatinSquareQuasigroup, public GeneratedObject {
    private:
        std::vector<int> generateAutomorphism();
    public:
        std::vector<int> alpha;
        std::vector<int> beta;
        int c;
    public:
        explicit AffineQuasigroup(int order, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };
}

#endif //QUASIGROUP_AFFINEQUASIGROUP_H
