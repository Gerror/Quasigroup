//
// Created by Gerror on 06.04.2022.
//

#include "FNQuasigroup.h"

namespace Quasigroup {


    FNQuasigroup::FNQuasigroup(const FeistelNetwork &feistelNetwork) : FunctionalQuasigroup(feistelNetwork) {}

    FNQuasigroup::FNQuasigroup(int k, unsigned long long int seed) : FNQuasigroup(FeistelNetwork(k, seed)) {}

    int FNQuasigroup::getProduct(int x, int y) const {
        int xArray[2];
        int yArray[2];
        int result[2];
        intValueToKArray(x, k, xArray, 2);
        intValueToKArray(y, k, yArray, 2);

        result[0] = functionFamily.getFunctionValue(mod(xArray[1] + yArray[1], k));
        result[1] = mod(xArray[0] + yArray[0] + functionFamily.getFunctionValue(mod(xArray[1] + yArray[1], k), 1) - yArray[1], k);
        return kArrayToIntValue(k, result, 2);
    }

}