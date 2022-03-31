//
// Created by Gerror on 18.02.2022.
//

#include "tests.h"

namespace Quasigroup {

    void checkCorrectnessLatinSquare(Quasigroup &q) {
        for (int i = 0; i < q.getOrder(); i++) {
            for (int j = 0; j < q.getOrder(); j++) {
                for (int m = 0; m < q.getOrder(); m++) {
                    if (m != i && m != j && (q.getProduct(i, m) == q.getProduct(i, j) || q.getProduct(m, j) == q.getProduct(i, j))) {
                        throw runtime_error("Test failed: is not quasigroup");
                    }
                }
            }
        }
    }

}