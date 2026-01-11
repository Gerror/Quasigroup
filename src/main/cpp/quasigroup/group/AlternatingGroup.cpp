#include "AlternatingGroup.h"

#include "utils/Helper.h"

namespace Quasigroup {
AlternatingGroup::AlternatingGroup(const int degree)
    : LatinSquareQuasigroup(factorial(degree) / 2) {
  int **permutations = generateAllEvenPermutations(degree);
  std::unordered_map<std::string, int> permutationStrToPosition;
  for (int i = 0; i < order; i++) {
    const auto permutation = permutations[i];
    auto permutationStr = permutationToString(permutation, degree);

    permutationStrToPosition[permutationStr] = i;
  }

  for (int x = 0; x < order; x++) {
    for (int y = 0; y < order; y++) {
      const auto xPermutation = permutations[x];
      const auto yPermutation = permutations[y];

      const auto xyProductPermutation =
          permutationProduct(xPermutation, yPermutation, degree);
      auto xyProductPermutationStr =
          permutationToString(xyProductPermutation, degree);

      latinSquare[x][y] = permutationStrToPosition[xyProductPermutationStr];

      delete[] xyProductPermutation;
    }
  }

  for (int i = 0; i < order; i++) {
    delete[] permutations[i];
  }
  delete[] permutations;
}
}  // namespace Quasigroup