//
// Created by rzhig on 04.03.2022.
//

#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <ostream>
#include <random>
#include <iostream>
#include <queue>
#include <ctime>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Неупорядоченная пара элементов, нужная
     * для проверки простоты
     */

    struct UnorderedPair {
        int firstElement;
        int secondElement;
    };

    /*
     * Абстрактный класс квазигрупп
     */

    class Quasigroup {
    public:
        virtual int getProduct(int x, int y) const = 0;
        int getOrder() const { return order; }
        unsigned long long int getSeed() const { return seed; }
        bool isAffine();
        bool isSimple();
        friend std::ostream &operator<<(std::ostream &out, const Quasigroup &q);
        friend bool operator==(const Quasigroup &q1, const Quasigroup &q2);
    protected:
        int order{};
        unsigned long long int seed{};
        std::mt19937 mersenne;

        virtual void generate() = 0;
        Quasigroup() = default;
    };

}

#endif //QUASIGROUP_QUASIGROUP_H
