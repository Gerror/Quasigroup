//
// Created by Gerror on 31.03.2022.
//

#include "FunctionalQuasigroup.h"

namespace Quasigroup {

    FunctionalQuasigroup::FunctionalQuasigroup(const FunctionFamily &functionFamily) {
        this->k = functionFamily.getK();
        this->n = functionFamily.getN();
        this->functionFamily = functionFamily;
        this->order = pow(k, n);
    }

    bool operator==(const FunctionalQuasigroup &q1, const FunctionalQuasigroup &q2) {
        return (q1.functionFamily == q2.functionFamily);
    }

}