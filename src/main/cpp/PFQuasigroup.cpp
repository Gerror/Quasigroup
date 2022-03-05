//
// Created by rzhig on 05.03.2022.
//

#include "PFQuasigroup.h"

namespace Quasigroup {

    PFQuasigroup::PFQuasigroup(int k, int n, unsigned long long int seed) {
        this->k = k;
        this->n = n;
        this->order = pow(k, n);
        this->seed = seed;
        this->mersenne = std::mt19937(seed);

        properFamilies = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamilies[i] = new int[order];
        }

        generate();
        generatePiValue();
    }

    PFQuasigroup::PFQuasigroup(std::ifstream &input) {
        if (!input.is_open()) {
            std::cerr << "Input PFQuasigroup from ifstream, but ifstream was not open" << std::endl;
            return;
        }

        input >> k >> n;
        order = pow(k, n);

        properFamilies = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamilies[i] = new int[order];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < order; j++) {
                input >> properFamilies[i][j];
            }
        }

        generatePiValue();
    }

    PFQuasigroup::~PFQuasigroup() {
        for (int i = 0; i < n; i++) {
            delete[] (properFamilies[i]);
        }
        delete[] (properFamilies);
        delete[] piValue;
    }

    void PFQuasigroup::generate() {
        int stepCount = STEP_COUNT;

        // Create default proper families
        for (int i = 0; i < n; i++) {
            int value = mersenne() % k;
            for (int j = 0; j < order; j++) {
                properFamilies[i][j] = value;
            }
        }

        for (int i = 0; i < stepCount; i++) {
            // algorithm step

            // generate variable number
            int number = mersenne() % n;

            // Поменять местами переменную number с последней
            int newProperFamily[n][order];
            for (int j = 0; j < n; j++) {
                for (int m = 0; m < order; m++) {
                    int kArray[n];
                    intValueToKArray(m, k, kArray, n);

                    int temp = kArray[number];
                    kArray[number] = kArray[n - 1];
                    kArray[n - 1] = temp;

                    newProperFamily[j][m] = properFamilies[j][kArrayToIntValue(k, kArray, n)];
                }
            }
            // Поменять местами функцию number с последней
            for (int j = 0; j < order; j++) {
                int temp = newProperFamily[number][j];
                newProperFamily[number][j] = newProperFamily[n - 1][j];
                newProperFamily[n - 1][j] = temp;
            }

            // Вернуть семейство как было
            for (int j = 0; j < n; j++) {
                for (int m = 0; m < order; m++) {
                    properFamilies[j][m] = newProperFamily[j][m];
                }
            }
            number = n - 1;

            // new k proper families, n - 1 function, n - 1 variables
            int size = pow(k, n - 1);
            int G[k][n - 1][size];
            for (int j = 0; j < k; j++) {
                for (int m = 0; m < n - 1; m++) {
                    for (int p = 0; p < size; p++) {
                        int kArray[n];
                        int newkArray[n - 1];
                        intValueToKArray(p, k, newkArray, n - 1);

                        kArray[n - 1] = j;
                        for (int q = 0; q < n - 1; q++) {
                            kArray[q] = newkArray[q];
                        }

                        G[j][m][p] = properFamilies[m][kArrayToIntValue(k, kArray, n)];
                    }
                }
            }

            // Create n - 1 function in new proper families. (Formula (2))
            for (int j = 0; j < n - 1; j++) {
                for (int m = 0; m < order; m++) {
                    int kArray[n];
                    int newkArray[n - 1];
                    intValueToKArray(m, k, kArray, n);

                    for (int q = 0; q < n - 1; q++) {
                        newkArray[q] = kArray[q];
                    }

                    int newValue = kArrayToIntValue(k, newkArray, n - 1);

                    int result = 0;
                    for (int p = 0; p < k; p++) {
                        result = max(result, min(unarFunction(kArray[n - 1], p, k), G[p][j][newValue], k), k);
                    }

                    properFamilies[j][m] = result;
                }
            }

            // Create graph
            std::vector<int> edges[size];
            bool used[size];
            for (int s = 0; s < size; s++) {
                used[s] = false;
                for (int t = s + 1; t < size; t++) {
                    int sArray[n - 1];
                    int tArray[n - 1];
                    intValueToKArray(s, k, sArray, n - 1);
                    intValueToKArray(t, k, tArray, n - 1);

                    // find pair G_{m}, G_{p}
                    bool needEdge = false;
                    for (int m = 0; m < k; m++) {
                        for (int p = m + 1; p < k; p++) {
                            bool isTruePair = true;
                            for (int j = 0; j < n - 1; j++) {
                                if (tArray[j] != sArray[j]) {
                                    if (G[m][j][t] == G[p][j][s]) {
                                        isTruePair = false;
                                    }
                                }
                            }
                            if (isTruePair) {
                                needEdge = true;
                            }
                        }
                    }

                    if (needEdge) {
                        edges[t].push_back(s);
                        edges[s].push_back(t);
                    }
                }
            }

            //calculate components and set value for last function
            std::vector<int> comp;
            for (int j = 0; j < size; j++) {
                if (!used[j]) {
                    comp.clear();
                    DFS(j, reinterpret_cast<std::vector<int> (&)[]>(edges), used, comp);

                    int value = mersenne() % k;
                    for (int m : comp) {
                        for (int p = 0; p < k; p++) {
                            properFamilies[n - 1][m * k + p] = value;
                        }
                    }
                }
            }
        }
    }

    void PFQuasigroup::generatePiValue() {
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
            qArray[m] = xArray[m] + yArray[m] + properFamilies[m][kArrayToIntValue(k, pi, n)];
            qArray[m] = qArray[m] % k;
        }

        return kArrayToIntValue(k, qArray, n);
    }

    int PFQuasigroup::getK() {
        return k;
    }

    int PFQuasigroup::getN() {
        return n;
    }

    std::ostream &operator<<(std::ostream &out, const PFQuasigroup &quasigroup) {
        for (int i = 0; i < quasigroup.n; i++) {
            for (int j = 0; j < quasigroup.order; j++) {
                out << quasigroup.properFamilies[i][j] << SEPARATOR;
            }
            out << NEW_LINE;
        }
        return out;
    }

    bool operator==(const PFQuasigroup &q1, const PFQuasigroup &q2) {
        if (q1.n != q2.n || q1.k != q2.k) {
            return false;
        }

        int n = q1.n;
        int order = q1.order;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < order; j++) {
                if (q1.properFamilies[i][j] != q2.properFamilies[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

}
