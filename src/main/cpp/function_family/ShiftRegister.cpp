#include "ShiftRegister.h"

namespace Quasigroup {

    ShiftRegister::ShiftRegister(int k, int n, unsigned long long int seed) :
    FunctionFamily(k, n, 1, pow(k, n - 1)), GeneratedObject(seed) {
        generate();
    }

    void ShiftRegister::generate() {
        for (int i = 0; i < getFunctionSize() / k; i++) {
            int kArray[n - 2];
            int newKArray[n - 1];
            intValueToKArray(i, k, kArray, n - 2);

            newKArray[0] = 0;
            for (int j = 0; j < n - 2; j++) {
                newKArray[j + 1] = kArray[j];
            }

            std::vector<int> randomPermutation = generateRandomPermutation(k, getSeed() + i);
            for (int j = 0; j < k; j++) {
                int kValue[n - 1];
                for (int m = 0; m < n - 1; m++) {
                    kValue[m] = (newKArray[m] + j) % k;
                }
                functionFamily[0][kArrayToIntValue(k, kValue, n - 1)] = randomPermutation[j];
            }
        }
    }

}