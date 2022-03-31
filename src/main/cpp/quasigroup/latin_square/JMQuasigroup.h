//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_JMQUASIGROUP_H
#define QUASIGROUP_JMQUASIGROUP_H

#include "IncidenceCube.h"
#include "LatinSquareQuasigroup.h"
#include "GeneratedObject.h"

namespace Quasigroup {

    /*
    * Quasigroups given by the Latin square and
    * generated by the Jacobson Matthews algorithm
    */

    class JMQuasigroup : public LatinSquareQuasigroup, public GeneratedObject {
    public:
        explicit JMQuasigroup(int order, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_JMQUASIGROUP_H
