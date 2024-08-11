#ifndef QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H
#define QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H

#include "GeneratedObject.h"
#include "AbelianGroup.h"

namespace Quasigroup {

    class AbelianGroupAutomorphism : public GeneratedObject {
    private:
        AbelianGroup *group;
        std::vector<int> images;
    public:
        explicit AbelianGroupAutomorphism(AbelianGroup *group, unsigned long long int seed = 0);

        int getImage(int x) const;

        bool isCorrectHomomorphism() const;

        friend std::ostream &operator<<(std::ostream &out, const AbelianGroupAutomorphism &a);

    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H
