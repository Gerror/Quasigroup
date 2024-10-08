#include "Helper.h"

namespace Quasigroup {

    std::vector<int> calculateReversePermutation(std::vector<int> permutation) {
        std::vector<int> revPermutation(permutation.size());

        for (unsigned int i = 0; i < permutation.size(); i++) {
            revPermutation[permutation[i]] = i;
        }

        return revPermutation;
    }

    int calculateUnorderedPairIndex(int t1, int t2, int order) {
        if (t2 < t1) {
            std::swap(t2, t1);
        }

        return t1 * order + t2 - ((t1 + 1) * (t1 + 2)) / 2;
    }

    int mergeUnorderedPairClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass) {
        // Всегда сливаем в первый класс
        if (fclass > sclass) {
            std::swap(fclass, sclass);
        }

        // Все элементы из второго класса перекидываем в первый и изменяем номер класса переброшенного элемента
        while (!classes[sclass].empty()) {
            classes[fclass].push_back(classes[sclass][classes[sclass].size() - 1]);
            classIndex[classes[sclass][classes[sclass].size() - 1]] = fclass;
            classes[sclass].pop_back();
        }

        return (int) classes[fclass].size();
    }

    void DFS(int v, std::vector<int> (&edges)[], bool *used, std::vector<int> &comp) {
        used[v] = true;
        comp.push_back(v);
        for (size_t i = 0; i < edges[v].size(); ++i) {
            int to = edges[v][i];
            if (!used[to]) {
                DFS(to, edges, used, comp);
            }
        }
    }

    void intValueToKArray(int value, int k, int *kArray, int size) {
        for (int i = 0; i < size; i++) {
            kArray[size - 1 - i] = value % k;
            value /= k;
        }
    }

    int kArrayToIntValue(int k, int *kArray, int size) {
        int result = 0;
        for (int i = 0; i < size; i++) {
            result += kArray[i] * pow(k, size - 1 - i);
        }
        return result;
    }

    int unarFunction(int x, int j, int k) {
        if (x % k == j % k) {
            return k - 1;
        }
        return 0;
    }


    int min(int a, int b, int k) {
        if (a % k < b % k) {
            return a;
        }
        return b;
    }

    int max(int a, int b, int k) {
        if (a % k > b % k) {
            return a;
        }
        return b;
    }

    std::vector<int> generateRandomPermutation(int size, unsigned long long int seed) {
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

    int mod(int value, int k) {
        return (value % k + k) % k;
    }

    std::tuple<int, double, double, double> increaseResult(std::tuple<int, double, double, double> &result, double time, bool sign, int size) {
        int count = std::get<0>(result);
        double worseTime = std::get<1>(result), averageTime = std::get<2>(result), bestTime = std::get<3>(result);
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

}