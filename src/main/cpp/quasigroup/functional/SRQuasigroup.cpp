#include "SRQuasigroup.h"

#include "utils/Helper.h"

namespace Quasigroup {
SRQuasigroup::SRQuasigroup(const ShiftRegister &shiftRegister,
                           const bool inverseOperations)
    : FunctionalQuasigroup(shiftRegister) {
  this->inverseOperations = inverseOperations;
  generate();
}

SRQuasigroup::SRQuasigroup(const int k, const int n,
                           const bool inverseOperations,
                           const unsigned long long int seed)
    : SRQuasigroup(ShiftRegister(k, n, seed), inverseOperations) {
  // no-op
}

void SRQuasigroup::generate() {
  for (int i = 0; i < order - 1; i++) {
    c.push_back(mersenne() % k);
  }
}

int SRQuasigroup::getProduct(const int x, const int y) const {
  int xArray[n];
  int yArray[n];
  int result[n];
  int gValue[n - 1];
  intValueToKArray(x, k, xArray, n);
  intValueToKArray(y, k, yArray, n);

  if (inverseOperations) {
    for (int i = 0; i < n - 1; i++) {
      gValue[i] = mod(xArray[i + 1] - yArray[i + 1], k);
      result[i] = mod(gValue[i] + yArray[i] + c[i], k);
    }
    result[n - 1] = mod(
        xArray[0] - yArray[0] + yArray[n - 1] +
            functionFamily.getFunctionValue(kArrayToIntValue(k, gValue, n - 1)),
        k);
  } else {
    for (int i = 0; i < n - 1; i++) {
      gValue[i] = mod(xArray[i + 1] + yArray[i + 1], k);
      result[i] = mod(gValue[i] - yArray[i] + c[i], k);
    }
    result[n - 1] = mod(
        xArray[0] + yArray[0] - yArray[n - 1] +
            functionFamily.getFunctionValue(kArrayToIntValue(k, gValue, n - 1)),
        k);
  }
  return kArrayToIntValue(k, result, n);
}
}  // namespace Quasigroup