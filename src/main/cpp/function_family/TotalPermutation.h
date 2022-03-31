//
// Created by rzhig on 06.03.2022.
//

#ifndef QUASIGROUP_TOTALPERMUTATION_H
#define QUASIGROUP_TOTALPERMUTATION_H

#include <ctime>
#include <random>
#include <iostream>

#include "Helper.h"
#include "FunctionFamily.h"
#include "GeneratedObject.h"

namespace Quasigroup {

    class TotalPermutation : public FunctionFamily, public GeneratedObject {
    public:
        TotalPermutation(int k, int n, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };

}


#endif //QUASIGROUP_TOTALPERMUTATION_H
