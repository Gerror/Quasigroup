#include "PFPermutatedQuasigroup.h"

#include "utils/Helper.h"

namespace Quasigroup {
PFPermutatedQuasigroup::PFPermutatedQuasigroup(
    const PFQuasigroup &original, const std::vector<int> &xPermutation,
    const std::vector<int> &yPermutation,
    const std::vector<int> &functionPermutation)
    : PFQuasigroup(original) {
  this->xPermutation = xPermutation;
  this->yPermutation = yPermutation;
  this->functionPermutation = functionPermutation;
}

int PFPermutatedQuasigroup::getProduct(const int x, const int y) const {
  int qArray[n];
  int xArray[n];
  int yArray[n];
  int pi[n];
  intValueToKArray(x, k, xArray, n);
  intValueToKArray(y, k, yArray, n);

  for (int m = 0; m < n; m++) {
    pi[m] = piValue[m * k * k + xArray[xPermutation[m]] * k +
                    yArray[yPermutation[m]]];
  }

  for (int m = 0; m < n; m++) {
    qArray[functionPermutation[m]] =
        mod(xArray[xPermutation[m]] + yArray[yPermutation[m]] +
                functionFamily.getFunctionValue(kArrayToIntValue(k, pi, n), m),
            k);
  }

  return kArrayToIntValue(k, qArray, n);
}

}  // namespace Quasigroup
