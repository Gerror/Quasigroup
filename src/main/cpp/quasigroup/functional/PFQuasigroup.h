#ifndef QUASIGROUP_PFQUASIGROUP_H
#define QUASIGROUP_PFQUASIGROUP_H

#include "FunctionalQuasigroup.h"
#include "GeneratedObject.h"
#include "ProperFamily.h"

namespace Quasigroup {

    /*
     * Quasigroups based on proper families of functions
     */

    class PFQuasigroup : public FunctionalQuasigroup, public GeneratedObject {
    private:
        int *piValue;
    public:
        int getProduct(int x, int y) const override;
        explicit PFQuasigroup(const ProperFamily& properFamily, unsigned long long int seed = 0);
        PFQuasigroup(int k, int n, unsigned long long int seed = 0);
        ~PFQuasigroup();
        friend bool operator==(const PFQuasigroup &q1, const PFQuasigroup &q2);
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_PFQUASIGROUP_H
