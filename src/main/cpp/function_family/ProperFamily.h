//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_PROPERFAMILY_H
#define QUASIGROUP_PROPERFAMILY_H

#define STEP_COUNT order * order

#include "FunctionFamily.h"
#include "GeneratedObject.h"
#include "Helper.h"

namespace Quasigroup {

    /*
     * Correct families of functions.
     * Used to generate quasigroups.
     */

    class ProperFamily : public FunctionFamily, public GeneratedObject {
    private:
        int order;
    public:
        int getOrder() const;
        ProperFamily(int k, int n, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_PROPERFAMILY_H
