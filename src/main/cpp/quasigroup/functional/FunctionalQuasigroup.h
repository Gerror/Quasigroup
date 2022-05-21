//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_FUNCTIONALQUASIGROUP_H
#define QUASIGROUP_FUNCTIONALQUASIGROUP_H

#include "Quasigroup.h"
#include "FunctionFamily.h"

namespace Quasigroup {

    /*
     * Quasigroups Defined Using Families of Functions
     */

    class FunctionalQuasigroup : public Quasigroup {
    public:
        explicit FunctionalQuasigroup(const FunctionFamily& functionFamily);
        friend bool operator==(const FunctionalQuasigroup &q1, const FunctionalQuasigroup &q2);
        FunctionFamily& getFunctionFamily();
    protected:
        int k;
        int n;
        FunctionFamily functionFamily;
    };

}

#endif //QUASIGROUP_FUNCTIONALQUASIGROUP_H
