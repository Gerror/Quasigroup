//
// Created by Gerror on 04.03.2022.
//

#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <ostream>
#include <random>
#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Неупорядоченные пары, необходимые для проверки простоты
     */

    struct UnorderedPair {
        int firstElement;
        int secondElement;
    };

    /*
     * Абстрактный класс квазигрупп
     */

    class Quasigroup {
    private:
        // Две функции, необходимые для поиска подквазигрупп
        int nextStep(unsigned int *step, int border) const;
        int checkStep(unsigned int *step,
                      int border, unsigned int *a_sq,
                      unsigned int *a_sqi, unsigned int *a_q) const;
    public:
        class QuasigroupHash {
        public:
            size_t operator() (const Quasigroup *quasigroup) const;
        };
        class QuasigroupEqualHash {
        public:
            bool operator()(const Quasigroup *q1, const Quasigroup *q2) const;
        };
        virtual int getProduct(int x, int y) const = 0;
        int getOrder() const;
        bool isAffine() const;
        bool isSimple() const;
        int findSubquasigroup(int border, unsigned int **a_sq) const;
        friend std::ostream &operator<<(std::ostream &out, const Quasigroup &q);
    protected:
        int order;
        Quasigroup() = default;
    };

}

#endif //QUASIGROUP_QUASIGROUP_H
