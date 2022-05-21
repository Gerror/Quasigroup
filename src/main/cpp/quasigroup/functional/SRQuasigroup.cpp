//
// Created by Gerror on 08.03.2022.
//

#include "SRQuasigroup.h"

namespace Quasigroup {

    SRQuasigroup::SRQuasigroup(const ShiftRegister &shiftRegister) : FunctionalQuasigroup(shiftRegister) {}

    SRQuasigroup::SRQuasigroup(int k, int n, unsigned long long int seed) : SRQuasigroup(ShiftRegister(k, n, seed)) {}

    int SRQuasigroup::getProduct(int x, int y) const {
        int xArray[n];
        int yArray[n];
        int result[n];
        int gValue[n - 1];
        intValueToKArray(x, k, xArray, n);
        intValueToKArray(y, k, yArray, n);

        for(int i = 0; i < n - 1; i++) {
            gValue[i] = mod(xArray[i + 1] + yArray[i + 1], k);
            result[i] = mod(gValue[i] - yArray[i], k);
        }
        result[n - 1] = mod(xArray[0] + yArray[0] - yArray[n - 1] + functionFamily.getFunctionValue(kArrayToIntValue(k, gValue, n - 1)), k);
        return kArrayToIntValue(k, result, n);
    }

}
