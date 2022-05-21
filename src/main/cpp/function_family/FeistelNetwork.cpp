//
// Created by Gerror on 06.04.2022.
//

#include "FeistelNetwork.h"

namespace Quasigroup {

    FeistelNetwork::FeistelNetwork(int k, unsigned long long int seed) :
    FunctionFamily(k, 2, 2, k), GeneratedObject(seed) {
        generate();
    }

    void FeistelNetwork::generate() {
        std::vector<int> s1 = generateRandomPermutation(k, getSeed());
        std::vector<int> s2 = generateRandomPermutation(k, getSeed() + 1);

        for (int x = 0; x < k; x++) {
            functionFamily[0][x] = s1[x];
            functionFamily[1][x] = mod(s2[x] - s1[x] + x, k);
        }
    }

}