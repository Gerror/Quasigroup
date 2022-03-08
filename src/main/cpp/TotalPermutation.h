//
// Created by rzhig on 06.03.2022.
//

#ifndef QUASIGROUP_TOTALPERMUTATION_H
#define QUASIGROUP_TOTALPERMUTATION_H

#include <ctime>
#include <random>
#include <iostream>

#include "Helper.h"

namespace Quasigroup {

    class TotalPermutation {
    private:
        int k;
        int n;
        int size;
        int *totalPermutation;
        unsigned long long int seed;
        std::mt19937 mersenne;
        void generate();
    public:
        TotalPermutation(int k, int n) : TotalPermutation(k, n, time(nullptr)) {};
        TotalPermutation(int k, int n, unsigned long long int seed);
        TotalPermutation(const TotalPermutation &tp);
        TotalPermutation() = default;
        ~TotalPermutation();
        int getGValue(int variable) const { return totalPermutation[variable]; }
        int getK() const { return k; }
        int getN() const { return n; }
        friend std::ostream &operator<<(std::ostream &out, const TotalPermutation &tp);
        friend bool operator==(const TotalPermutation &tp1, const TotalPermutation &tp2);
        TotalPermutation & operator = (const TotalPermutation & tp);
    };

}


#endif //QUASIGROUP_TOTALPERMUTATION_H
