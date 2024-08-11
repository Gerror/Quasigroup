#ifndef QUASIGROUP_SHIFTREGISTER_H
#define QUASIGROUP_SHIFTREGISTER_H

#include <ctime>
#include <random>
#include <iostream>

#include "utils/Helper.h"
#include "FunctionFamily.h"
#include "generator/GeneratedObject.h"

namespace Quasigroup {

    class ShiftRegister : public FunctionFamily, public GeneratedObject {
    public:
        ShiftRegister(int k, int n, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };

}


#endif //QUASIGROUP_SHIFTREGISTER_H
