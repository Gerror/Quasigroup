#ifndef QUASIGROUP_AFFINEQUASIGROUP_H
#define QUASIGROUP_AFFINEQUASIGROUP_H

#include <vector>
#include <function/AbelianGroupAutomorphism.h>

#include "generator/GeneratedObject.h"
#include "LatinSquareQuasigroup.h"

namespace Quasigroup {

    class AffineQuasigroup : public LatinSquareQuasigroup, public GeneratedObject {
    private:
        AbelianGroup *abelianGroup;
        AbelianGroupAutomorphism *alpha;
        AbelianGroupAutomorphism *beta;
        int c;
    public:
        AffineQuasigroup(int order, unsigned long long int seed = 0);
        ~AffineQuasigroup();

        AbelianGroup* getAbelianGroup() const;
        AbelianGroupAutomorphism* getAlpha() const;
        AbelianGroupAutomorphism* getBeta() const;
        int getC() const;
    protected:
        void generate() override;
    };
}

#endif //QUASIGROUP_AFFINEQUASIGROUP_H
