#include "AlternatingGroup.h"

namespace Quasigroup {

    AlternatingGroup::AlternatingGroup(int degree) : LatinSquareQuasigroup(factorial(degree) / 2) {
        int **permutations = generateAllEvenPermutations(degree);
        std::unordered_map<std::string, int> permutationStrToPosition;
        for (int i = 0; i < order; i++) {
            auto permutation = permutations[i];
            auto permutationStr = permutationToString(permutation, degree);

            permutationStrToPosition[permutationStr] = i;
        }

        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                auto xPermutation = permutations[x];
                auto yPermutation = permutations[y];

                auto xyProductPermutation = permutationProduct(xPermutation, yPermutation, degree);
                auto xyProductPermutationStr = permutationToString(xyProductPermutation, degree);

                latinSquare[x][y] = permutationStrToPosition[xyProductPermutationStr];

                delete[] xyProductPermutation;
            }
        }

        for (int i = 0; i < order; i++) {
            delete[] permutations[i];
        }
        delete[] permutations;
    }

}
