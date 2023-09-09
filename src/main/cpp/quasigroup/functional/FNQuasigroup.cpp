#include "FNQuasigroup.h"

namespace Quasigroup {


    FNQuasigroup::FNQuasigroup(const FeistelNetwork &feistelNetwork, bool inverseOperations) : FunctionalQuasigroup(feistelNetwork) {
        this->inverseOperations = inverseOperations;
    }

    FNQuasigroup::FNQuasigroup(int k, bool inverseOperations, unsigned long long int seed) : FNQuasigroup(FeistelNetwork(k, seed), inverseOperations) {
        // no-op
    }

    int FNQuasigroup::getProduct(int x, int y) const {
        int xArray[2];
        int yArray[2];
        int result[2];
        intValueToKArray(x, k, xArray, 2);
        intValueToKArray(y, k, yArray, 2);

        if (inverseOperations) {
            result[0] = mod(functionFamily.getFunctionValue(mod(xArray[1] - yArray[1], k)) + yArray[0], k);
            result[1] = mod(xArray[0] - yArray[0] +
                            functionFamily.getFunctionValue(mod(xArray[1] - yArray[1], k), 1) + yArray[1], k);
        } else {
            result[0] = mod(functionFamily.getFunctionValue(mod(xArray[1] + yArray[1], k)) - yArray[0], k);
            result[1] = mod(xArray[0] + yArray[0] +
                            functionFamily.getFunctionValue(mod(xArray[1] + yArray[1], k), 1) - yArray[1], k);
        }
        return kArrayToIntValue(k, result, 2);
    }

}