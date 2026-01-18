#include "PFQuasigroupPermutationTransformer.h"

#include "PFPermutatedQuasigroup.h"
#include "utils/Helper.h"

namespace Quasigroup {

PFQuasigroup* PFQuasigroupPermutationTransformer::transform(
    const PFQuasigroup* original) {
  const auto xPermutation =
      generateRandomPermutation(original->getFunctionFamily().getN());
  const auto yPermutation =
      generateRandomPermutation(original->getFunctionFamily().getN());
  const auto functionPermutation = generateRandomPermutation(
      original->getFunctionFamily().getNumberOfFunctions());

  return new PFPermutatedQuasigroup(*original, xPermutation, yPermutation,
                                    functionPermutation);
}

}  // namespace Quasigroup
