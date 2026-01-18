#include "ProperFamily.h"

#include "utils/Helper.h"

namespace Quasigroup {
ProperFamily::ProperFamily(const int k, const int n,
                           const unsigned long long int seed)
    : FunctionFamily(k, n, n, pow(k, n)),
      GeneratedObject(seed),
      order(pow(k, n)) {
  ProperFamily::generate();
}

ProperFamily::ProperFamily(const int k, const int n, int** functionFamily)
    : FunctionFamily(k, n, n, pow(k, n), functionFamily), order(pow(k, n)) {}

void ProperFamily::generate() {
  const int stepCount = STEP_COUNT;

  // Create default proper families
  for (int i = 0; i < n; i++) {
    const int value = mersenne() % k;
    for (int j = 0; j < order; j++) {
      functionFamily[i][j] = value;
    }
  }

  for (int i = 0; i < stepCount; i++) {
    // algorithm step

    // generate variable number
    int number = mersenne() % n;
    const int oldNumber = number;

    int newProperFamily[n][order];

    // Поменять местами переменную number с последней
    for (int j = 0; j < n; j++) {
      for (int m = 0; m < order; m++) {
        int kArray[n];
        intValueToKArray(m, k, kArray, n);

        const int temp = kArray[number];
        kArray[number] = kArray[n - 1];
        kArray[n - 1] = temp;

        newProperFamily[j][m] =
            functionFamily[j][kArrayToIntValue(k, kArray, n)];
      }
    }
    // Поменять местами функцию number с последней
    for (int j = 0; j < order; j++) {
      const int temp = newProperFamily[number][j];
      newProperFamily[number][j] = newProperFamily[n - 1][j];
      newProperFamily[n - 1][j] = temp;
    }

    // Присвоить текущему семейству значения нового
    for (int j = 0; j < n; j++) {
      for (int m = 0; m < order; m++) {
        functionFamily[j][m] = newProperFamily[j][m];
      }
    }
    number = n - 1;

    // new k proper families, n - 1 function, n - 1 variables
    const int size = pow(k, n - 1);
    int G[k][n - 1][size];
    for (int j = 0; j < k; j++) {
      for (int m = 0; m < n - 1; m++) {
        for (int p = 0; p < size; p++) {
          int kArray[n];
          int newKArray[n - 1];
          intValueToKArray(p, k, newKArray, n - 1);

          kArray[n - 1] = j;
          for (int q = 0; q < n - 1; q++) {
            kArray[q] = newKArray[q];
          }

          G[j][m][p] = functionFamily[m][kArrayToIntValue(k, kArray, n)];
        }
      }
    }

    // Create n - 1 function in new proper families. (Formula (2))
    for (int j = 0; j < n - 1; j++) {
      for (int m = 0; m < order; m++) {
        int kArray[n];
        int newKArray[n - 1];
        intValueToKArray(m, k, kArray, n);

        for (int q = 0; q < n - 1; q++) {
          newKArray[q] = kArray[q];
        }

        const int newValue = kArrayToIntValue(k, newKArray, n - 1);

        int result = 0;
        for (int p = 0; p < k; p++) {
          result = max(
              result,
              min(unarFunction(kArray[n - 1], p, k), G[p][j][newValue], k), k);
        }

        functionFamily[j][m] = result;
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

    // calculate components and set value for last function
    std::vector<int> comp;
    for (int j = 0; j < size; j++) {
      if (!used[j]) {
        comp.clear();
        DFS(j, reinterpret_cast<std::vector<int>(&)[]>(edges), used, comp);

        const int value = mersenne() % k;
        for (const int m : comp) {
          for (int p = 0; p < k; p++) {
            functionFamily[n - 1][m * k + p] = value;
          }
        }
      }
    }

    int properFamily[n][order];
    // Возвращаем обратно n-ю переменную и n-ю функцию
    //  Поменять местами переменную number с последней
    for (int j = 0; j < n; j++) {
      for (int m = 0; m < order; m++) {
        int kArray[n];
        intValueToKArray(m, k, kArray, n);

        const int temp = kArray[oldNumber];
        kArray[oldNumber] = kArray[n - 1];
        kArray[n - 1] = temp;

        properFamily[j][m] = functionFamily[j][kArrayToIntValue(k, kArray, n)];
      }
    }
    // Поменять местами функцию number с последней
    for (int j = 0; j < order; j++) {
      const int temp = properFamily[oldNumber][j];
      properFamily[oldNumber][j] = properFamily[n - 1][j];
      properFamily[n - 1][j] = temp;
    }

    // Присвоить текущему семейству значения нового
    for (int j = 0; j < n; j++) {
      for (int m = 0; m < order; m++) {
        functionFamily[j][m] = properFamily[j][m];
      }
    }
  }
}

int ProperFamily::getOrder() const { return order; }
}  // namespace Quasigroup