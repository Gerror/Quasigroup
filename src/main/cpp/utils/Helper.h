#ifndef QUASIGROUP_HELPER_H
#define QUASIGROUP_HELPER_H


#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <tuple>

namespace Quasigroup {

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

    // Ставит числу value в соответствие число из кольца вычетов по модулю k
    int mod(int value, int k);

    std::vector<int> generateRandomPermutation(int size, unsigned long long int seed = time(NULL));

    /*
     * Кортеж вида <count, worstTime, averageTime, bestTime>
     * Добавляет 1 к count, если sign = true и меняет кортеж result в зависимости от time
     * size - размер множества, над которым проводится тестирование
     */
    std::tuple<int, double, double, double> increaseResult(std::tuple<int, double, double, double> &result, double time, bool sign, int size);

}

#endif //QUASIGROUP_HELPER_H
