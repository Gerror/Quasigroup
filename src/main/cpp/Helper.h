//
// Created by Gerror on 05.03.2022.
//

#ifndef QUASIGROUP_HELPER_H
#define QUASIGROUP_HELPER_H


#include <vector>
#include <math.h>

namespace Quasigroup {

    void swapLines(std::vector<int> *matrix, int i, int j, int order);

    bool isSymmetricMatrix(std::vector<int> matrix, int order);

    std::vector<int> calculateReversePermutation(std::vector<int> permutation);

    int calculateUnorderedPairIndex(int t1, int t2, int order);

    // @return размер полученного класса
    int mergeUnorderedPairClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass);

    void DFS(int v, std::vector<int> (&edges)[], bool *used, std::vector<int> &comp);

    // Конвертирование целого числа десятичной системы в k-ичный вектор
    void intValueToKArray(int value, int k, int *kArray, int size);

    // Конвертирование k-ичного вектора в целое число в десяточной системе
    int kArrayToIntValue(int k, int *kArray, int size);

    int unarFunction(int x, int j, int k);

    int min(int a, int b, int k);

    int max(int a, int b, int k);
}

#endif //QUASIGROUP_HELPER_H
