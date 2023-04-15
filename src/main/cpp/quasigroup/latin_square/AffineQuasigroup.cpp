#include "AffineQuasigroup.h"

namespace Quasigroup {

    AffineQuasigroup::AffineQuasigroup(int order, unsigned long long int seed) : LatinSquareQuasigroup(order), GeneratedObject(seed) {
        generate();
    }

    void AffineQuasigroup::generate() {
        alpha = generateAutomorphism();
        beta = generateAutomorphism();
        c = mersenne() % order;

        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                latinSquare[x][y] = mod(alpha[x] + beta[y] + c, order);
            }
        }
    }

    std::vector<int> AffineQuasigroup::generateAutomorphism() {
        std::vector<int> v;
        v.push_back(0);

        int e = (mersenne() % (order - 1) + 1);
        v.push_back(e);

        for(int i = 2; i < order; i++) {
            v.push_back(mod(i * e, order));
        }
        return v;
    }

}