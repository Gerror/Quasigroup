//
// Created by rzhig on 06.03.2022.
//

#include "TotalPermutation.h"

namespace Quasigroup {


    TotalPermutation::TotalPermutation(int k, int n, unsigned long long int seed) {
        this->k = k;
        this->n = n;
        this->seed = seed;
        this->mersenne = std::mt19937(seed);
        this->size = pow(k, n - 2);

        totalPermutation = new int[(int) pow(k, n - 1)];
        generate();
    }

    TotalPermutation::TotalPermutation(const TotalPermutation &tp) {
        this->k = tp.k;
        this->n = tp.n;
        this->seed = tp.seed;
        this->mersenne = tp.mersenne;
        this->size = tp.size;

        totalPermutation = new int[(int) pow(k, n - 1)];
        for (int i = 0; i < pow(k, n - 1); i++) {
            totalPermutation[i] = tp.totalPermutation[i];
        }
    }

    TotalPermutation::~TotalPermutation() {
        delete[] totalPermutation;
    }

    void TotalPermutation::generate() {
        for (int i = 0; i < size; i++) {
            int kArray[n - 2];
            int newKArray[n - 1];
            intValueToKArray(i, k, kArray, n - 2);

            newKArray[0] = 0;
            for (int j = 0; j < n - 2; j++) {
                newKArray[j + 1] = kArray[j];
            }

            std::vector<int> randomPermutation = generateRandomPermutation(k, seed + i);
            for (int j = 0; j < k; j++) {
                int kValue[n - 1];
                for (int m = 0; m < n - 1; m++) {
                    kValue[m] = (newKArray[m] + j) % k;
                }
                totalPermutation[kArrayToIntValue(k, kValue, n - 1)] = randomPermutation[j];
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, const TotalPermutation &tp) {
        int maxValue = pow(tp.k, tp.n - 1);
        for (int i = 0; i < maxValue; i++) {
            out << tp.totalPermutation[i];
        }
        return out;
    }

    bool operator==(const TotalPermutation &tp1, const TotalPermutation &tp2) {
        if (tp1.k != tp2.k || tp1.n != tp2.n) {
            return false;
        }

        int size = tp1.size; // tp1.size == tp2.size

        for (int i = 0; i < size; i++) {
            if (tp1.totalPermutation[i] != tp2.totalPermutation[i]) {
                return false;
            }
        }

        return true;
    }

    TotalPermutation &TotalPermutation::operator=(const TotalPermutation &tp) {
        if (this != &tp) {
            this->k = tp.k;
            this->n = tp.n;
            this->seed = tp.seed;
            this->mersenne = tp.mersenne;
            this->size = tp.size;

            totalPermutation = new int[(int) pow(k, n - 1)];
            for (int i = 0; i < pow(k, n - 1); i++) {
                totalPermutation[i] = tp.totalPermutation[i];
            }
        }
        return *this;
    }

}