#include "FeistelNetwork.h"

#include "utils/Helper.h"

namespace Quasigroup {
FeistelNetwork::FeistelNetwork(const int k, const unsigned long long int seed)
    : FunctionFamily(k, 2, 2, k), GeneratedObject(seed) {
  FeistelNetwork::generate();
}

void FeistelNetwork::generate() {
  const std::vector<int> s1 = generateRandomPermutation(k, getSeed());
  const std::vector<int> s2 = generateRandomPermutation(k, getSeed() + 1);

  for (int x = 0; x < k; x++) {
    functionFamily[0][x] = s1[x];
    functionFamily[1][x] = mod(s2[x] - s1[x] + x, k);
  }
}
}  // namespace Quasigroup
