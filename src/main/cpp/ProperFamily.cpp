//
// Created by rzhig on 06.03.2022.
//

#include "ProperFamily.h"

namespace Quasigroup {

    ProperFamily::ProperFamily(int k, int n, unsigned long long int seed) {
        this->k = k;
        this->n = n;
        this->order = pow(k, n);
        this->seed = seed;
        this->mersenne = std::mt19937(seed);

        properFamily = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamily[i] = new int[order];
        }

        generate();
    }

    ProperFamily::ProperFamily(std::ifstream &input) {
        if (!input.is_open()) {
            std::cerr << "Input PFQuasigroup from ifstream, but ifstream was not open" << std::endl;
            return;
        }

        input >> k >> n;
        order = pow(k, n);

        properFamily = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamily[i] = new int[order];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < order; j++) {
                input >> properFamily[i][j];
            }
        }

    }

    ProperFamily::ProperFamily(const ProperFamily &pf) {
        this->k = pf.k;
        this->n = pf.n;
        this->order = pf.order;
        this->seed = pf.seed;
        this->mersenne = pf.mersenne;

        properFamily = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamily[i] = new int[order];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < order; j++) {
                this->properFamily[i][j] = pf.properFamily[i][j];
            }
        }
    }

    ProperFamily &ProperFamily::operator=(const ProperFamily &pf) {
        if (this != &pf) {
            this->k = pf.k;
            this->n = pf.n;
            this->order = pf.order;
            this->seed = pf.seed;
            this->mersenne = pf.mersenne;

            properFamily = new int *[n];
            for (int i = 0; i < n; i++) {
                properFamily[i] = new int[order];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < order; j++) {
                    this->properFamily[i][j] = pf.properFamily[i][j];
                }
            }
        }
        return *this;
    }

    ProperFamily::~ProperFamily() {
        for (int i = 0; i < n; i++) {
            delete[] (properFamily[i]);
        }
        delete[] (properFamily);
    }

    void ProperFamily::generate() {
        int stepCount = STEP_COUNT;

        // Create default proper families
        for (int i = 0; i < n; i++) {
            int value = mersenne() % k;
            for (int j = 0; j < order; j++) {
                properFamily[i][j] = value;
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

                    newProperFamily[j][m] = properFamily[j][kArrayToIntValue(k, kArray, n)];
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
                    properFamily[j][m] = newProperFamily[j][m];
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

                        G[j][m][p] = properFamily[m][kArrayToIntValue(k, kArray, n)];
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

                    properFamily[j][m] = result;
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
                            properFamily[n - 1][m * k + p] = value;
                        }
                    }
                }
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, const ProperFamily &pf) {
        for (int i = 0; i < pf.getN(); i++) {
            for (int j = 0; j < pf.getOrder(); j++) {
                out << pf.getFunctionValue(i, j) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    bool operator==(const ProperFamily &pf1, const ProperFamily &pf2) {
        if (pf1.getN() != pf2.getN() || pf1.getK() != pf2.getK()) {
            return false;
        }

        int n = pf1.getN();
        int order = pf1.getOrder();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < order; j++) {
                if (pf1.getFunctionValue(i, j) != pf2.getFunctionValue(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }
}