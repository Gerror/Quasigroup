#include "PFQuasigroup.h"

namespace Quasigroup {

    PFQuasigroup::PFQuasigroup(const ProperFamily &properFamily, unsigned long long int seed) : FunctionalQuasigroup(properFamily) {
        piValue = new int[n * k * k];
        generate();
    }

    PFQuasigroup::PFQuasigroup(int k, int n, unsigned long long int seed) : PFQuasigroup(ProperFamily(k, n, seed), seed) {}

    PFQuasigroup::~PFQuasigroup() {
        delete [] piValue;
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
            qArray[m] = xArray[m] + yArray[m] + functionFamily.getFunctionValue(kArrayToIntValue(k, pi, n), m);
            qArray[m] = qArray[m] % k;
        }

        return kArrayToIntValue(k, qArray, n);
    }

    void PFQuasigroup::generate() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                for (int m = 0; m < k; m++) {
                    piValue[i * k * k + j * k + m] = mersenne() % k;
                }
            }
        }
    }

    bool operator==(const PFQuasigroup &q1, const PFQuasigroup &q2) {
        if (!(q1.functionFamily == q2.functionFamily)) {
            return false;
        }

        int n = q1.functionFamily.getN();
        int k = q1.functionFamily.getK();

        for (int i = 0; i < n * k * k; i++) {
            if (q1.piValue[i] != q2.piValue[i]) {
                return false;
            }
        }

        return true;
    }

}