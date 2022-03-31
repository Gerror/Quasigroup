//
// Created by Gerror on 18.02.2022.
//

#include "tests.h"

namespace Quasigroup {

    bool checkCorrectnessLatinSquare(Quasigroup &q) {
        for (int i = 0; i < q.getOrder(); i++) {
            for (int j = 0; j < q.getOrder(); j++) {
                for (int m = 0; m < q.getOrder(); m++) {
                    if (m != i && m != j && (q.getProduct(i, m) == q.getProduct(i, j) || q.getProduct(m, j) == q.getProduct(i, j))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool checkCorrectnessProperFamily(ProperFamily &pf) {
        for (int i = 0; i < pf.getOrder(); i++)
        {
            for (int j = i + 1; j < pf.getOrder(); j++)
            {
                int s[pf.getN()];
                int t[pf.getN()];
                intValueToKArray(i, pf.getK(), s, pf.getN());
                intValueToKArray(j, pf.getK(), t, pf.getN());

                bool truePair = false;
                for (int m = 0; m < pf.getN(); m++)
                {
                    if (s[m] != t[m] && pf.getFunctionValue(i, m) == pf.getFunctionValue(j, m)) {
                        truePair = true;
                    }
                }
                if (!truePair) {
                    return false;
                }
            }
        }
        return true;
    }

}