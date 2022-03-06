//
// Created by rzhig on 06.03.2022.
//

#ifndef QUASIGROUP_PROPERFAMILY_H
#define QUASIGROUP_PROPERFAMILY_H

#define STEP_COUNT order * order

#include <ostream>
#include <fstream>
#include <ctime>
#include <random>
#include <iostream>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Правильные семейства функций.
     * Используются для генерации квазигрупп.
     */

    class ProperFamily {
    private:
        int k{};
        int n{};
        int **properFamily{};
        int order{};
        std::mt19937 mersenne;
        unsigned long long int seed{};
        void generate();
    public:
        ProperFamily(int k, int n, unsigned long long int seed);
        ProperFamily(int k, int n) : ProperFamily(k, n, time(nullptr)) {}
        explicit ProperFamily(std::ifstream &input);
        ProperFamily(const ProperFamily &pf);
        ProperFamily() = default;
        ~ProperFamily();
        int getK() const { return k; }
        int getN() const { return n; }
        int getOrder() const { return order; }
        unsigned long long int getSeed() const { return seed; }
        int getFunctionValue(int functionNumber, int varValue) const { return properFamily[functionNumber][varValue]; }
        friend std::ostream &operator<<(std::ostream &out, const ProperFamily &pf);
        friend bool operator==(const ProperFamily &pf1, const ProperFamily &pf2);
        ProperFamily & operator = (const ProperFamily & pf);
    };

}


#endif //QUASIGROUP_PROPERFAMILY_H
