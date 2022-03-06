//
// Created by rzhig on 05.03.2022.
//

#include "PFQuasigroup.h"

namespace Quasigroup {

    PFQuasigroup::PFQuasigroup(const ProperFamily& properFamily, unsigned long long int seed) {
        this->properFamily = properFamily;
        this->k = properFamily.getK();
        this->n = properFamily.getN();
        this->order = properFamily.getOrder();
        this->seed = seed;
        this->mersenne = std::mt19937(seed);

        generate();
    }

    PFQuasigroup::~PFQuasigroup() {
        delete[] piValue;
    }

    void PFQuasigroup::generate() {
        piValue = new int[n * k * k];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                for (int m = 0; m < k; m++) {
                    piValue[i * k * k + j * k + m] = mersenne() % k;
                }
            }
        }
    }

    int PFQuasigroup::getProduct(int x, int y) const {
        int qArray[n];
        int xArray[n];
        int yArray[n];
        int pi[n];
        intValueToKArray(x, k, xArray, n);
        intValueToKArray(y, k, yArray, n);

        for (int m = 0; m < n; m++) {
            pi[m] = piValue[m * k * k + xArray[m] * k + yArray[m]];
        }

        for (int m = 0; m < n; m++) {
            qArray[m] = xArray[m] + yArray[m] + properFamily.getFunctionValue(m, kArrayToIntValue(k, pi, n));
            qArray[m] = qArray[m] % k;
        }

        return kArrayToIntValue(k, qArray, n);
    }

}
