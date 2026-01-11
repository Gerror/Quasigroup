#include "Helper.h"

namespace Quasigroup {
std::vector<int> calculateReversePermutation(
    const std::vector<int> &permutation) {
  std::vector<int> revPermutation(permutation.size());

  for (unsigned int i = 0; i < permutation.size(); i++) {
    revPermutation[permutation[i]] = i;
  }

  return revPermutation;
}

int calculateUnorderedPairIndex(int t1, int t2, const int order) {
  if (t2 < t1) {
    std::swap(t2, t1);
  }

  return t1 * order + t2 - ((t1 + 1) * (t1 + 2)) / 2;
}

int mergeUnorderedPairClasses(std::vector<int> *classes, int *classIndex,
                              int fClass, int sclass) {
  // Всегда сливаем в первый класс
  if (fClass > sclass) {
    std::swap(fClass, sclass);
  }

  // Все элементы из второго класса перекидываем в первый и изменяем номер
  // класса переброшенного элемента
  while (!classes[sclass].empty()) {
    classes[fClass].push_back(classes[sclass][classes[sclass].size() - 1]);
    classIndex[classes[sclass][classes[sclass].size() - 1]] = fClass;
    classes[sclass].pop_back();
  }

  return static_cast<int>(classes[fClass].size());
}

void DFS(const int v, std::vector<int> (&edges)[], bool *used,
         std::vector<int> &comp) {
  used[v] = true;
  comp.push_back(v);
  for (size_t i = 0; i < edges[v].size(); ++i) {
    if (const int to = edges[v][i]; !used[to]) {
      DFS(to, edges, used, comp);
    }
  }
}

void intValueToKArray(int value, const int k, int *kArray, const int size) {
  for (int i = 0; i < size; i++) {
    kArray[size - 1 - i] = value % k;
    value /= k;
  }
}

int kArrayToIntValue(const int k, const int *kArray, const int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    result += kArray[i] * pow(k, size - 1 - i);
  }
  return result;
}

int unarFunction(const int x, const int j, const int k) {
  if (x % k == j % k) {
    return k - 1;
  }
  return 0;
}

int min(const int a, const int b, const int k) {
  if (a % k < b % k) {
    return a;
  }
  return b;
}

int max(const int a, const int b, const int k) {
  if (a % k > b % k) {
    return a;
  }
  return b;
}

std::vector<int> generateRandomPermutation(const int size,
                                           const unsigned long long int seed) {
  std::vector<int> result;
  std::mt19937 mersenne(seed);
  for (int i = 0; i <= size - 1; i++) {
    result.push_back(i);
  }
  for (int i = 0; i < size - 1; i++) {
    int j = mersenne() % (size - i) + i;
    std::swap(result[i], result[j]);
  }
  return result;
}

int mod(const int value, const int k) { return (value % k + k) % k; }

std::tuple<int, double, double, double> increaseResult(
    const std::tuple<int, double, double, double> &result, const double time,
    const bool sign, const int size) {
  int count = std::get<0>(result);
  double worseTime = std::get<1>(result), averageTime = std::get<2>(result),
         bestTime = std::get<3>(result);
  if (sign) {
    count++;
  }

  averageTime += time / size;
  if (time > worseTime) {
    worseTime = time;
  }

  if (bestTime < 0 || time < bestTime) {
    bestTime = time;
  }

  return {count, worseTime, averageTime, bestTime};
}

int factorial(const int n) {
  int result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}

int **generateAllPermutations(const int n) {
  int original[n];
  for (int i = 0; i < n; i++) {
    original[i] = i;
  }

  const auto result = new int *[factorial(n)];
  int i = 0;
  do {
    const auto permutation = new int[n];

    for (int j = 0; j < n; j++) {
      permutation[j] = original[j];
    }

    result[i] = permutation;
    i++;
  } while (std::next_permutation(original, original + n));

  return result;
}

int **generateAllPermutationsWithSign(const int n, const int sign) {
  int **allPermutations = generateAllPermutations(n);

  const int nFactorial = factorial(n);
  auto **filteredPermutation = new int *[nFactorial / 2];

  int counter = 0;
  for (int i = 0; i < nFactorial; i++) {
    if (int *permutation = allPermutations[i];
        calculatePermutationSign(permutation, n) == sign) {
      filteredPermutation[counter] = permutation;
      counter++;
    } else {
      delete[] permutation;
    }
  }
  delete[] allPermutations;

  return filteredPermutation;
}

int **generateAllEvenPermutations(const int n) {
  return generateAllPermutationsWithSign(n, 0);
}

int **generateAllOddPermutations(const int n) {
  return generateAllPermutationsWithSign(n, 1);
}

uint calculatePermutationSign(const int *permutation, const int n) {
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (permutation[i] > permutation[j]) {
        cnt++;
      }
    }
  }
  return cnt % 2;
}

int *permutationProduct(const int *left, const int *right, const int n) {
  const auto result = new int[n];

  for (int i = 0; i < n; i++) {
    result[i] = left[right[i]];
  }

  return result;
}

std::string permutationToString(const int *permutation, const int n) {
  std::ostringstream oss("");

  for (int i = 0; i < n; i++) {
    oss << permutation[i] << " ";
  }

  return oss.str();
}

std::vector<int> transmutationFromCycle(const std::vector<int> &cycle,
                                        const int size) {
  std::vector<int> result(size);
  std::iota(std::begin(result), std::end(result), 0);

  for (int i = -1; i < static_cast<int>(cycle.size()) - 1; i++) {
    if (i == -1) {
      result[cycle[cycle.size() - 1]] = cycle[0];
    } else {
      result[cycle[i]] = cycle[i + 1];
    }
  }

  return result;
}
}  // namespace Quasigroup
