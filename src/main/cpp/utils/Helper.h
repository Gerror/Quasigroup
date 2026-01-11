#ifndef QUASIGROUP_HELPER_H
#define QUASIGROUP_HELPER_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <sstream>
#include <tuple>
#include <vector>

namespace Quasigroup {
int calculateUnorderedPairIndex(int t1, int t2, int order);

// @return размер полученного класса
int mergeUnorderedPairClasses(std::vector<int> *classes, int *classIndex,
                              int fClass, int sclass);

void DFS(int v, std::vector<int> (&edges)[], bool *used,
         std::vector<int> &comp);

// Конвертирование целого числа десятичной системы в k-ичный вектор
void intValueToKArray(int value, int k, int *kArray, int size);

// Конвертирование k-ичного вектора в целое число в десятичной системе
int kArrayToIntValue(int k, const int *kArray, int size);

int unarFunction(int x, int j, int k);

int min(int a, int b, int k);

int max(int a, int b, int k);

// Ставит числу value в соответствие число из кольца вычетов по модулю k
int mod(int value, int k);

std::vector<int> generateRandomPermutation(
    int size, unsigned long long int seed = time(nullptr));

/*
 * Кортеж вида <count, worstTime, averageTime, bestTime>
 * Добавляет 1 к count, если sign = true и меняет кортеж result в зависимости от
 * time size - размер множества, над которым проводится тестирование
 */
std::tuple<int, double, double, double> increaseResult(
    const std::tuple<int, double, double, double> &result, double time,
    bool sign, int size);

int factorial(int n);

int **generateAllPermutations(int n);

int **generateAllPermutationsWithSign(int n, int sign);

int **generateAllEvenPermutations(int n);

int **generateAllOddPermutations(int n);

uint calculatePermutationSign(const int *permutation, int n);

int *permutationProduct(const int *left, const int *right, int n);

std::string permutationToString(const int *permutation, int n);

std::vector<int> transmutationFromCycle(const std::vector<int> &cycle,
                                        int size);
}  // namespace Quasigroup

#endif  // QUASIGROUP_HELPER_H