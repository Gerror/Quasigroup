#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <ostream>
#include <random>
#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <unordered_set>
#include <memory>

#include "Helper.h"

namespace Quasigroup {

    /*
     * Unordered pairs needed for simplicity test
     */

    struct UnorderedPair {
        int firstElement;
        int secondElement;
    };

    /*
     * Abstract class of finite 2-quasigroups
     */

    class Quasigroup {
    private:
        // Two functions needed to find subquasigroups
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
        bool isAffine(bool useLightTest = true) const;
        bool isSimple() const;
        bool isPolynomiallyComplete() const;
        bool isAssociative() const;
        bool isAssociativeByLightTest() const;
        bool isCommutative() const;
        bool isIdempotent() const;
        bool hasLeftUnit() const;
        bool hasRightUnit() const;
        bool isShapeless() const;
        bool isLoop() const;
        bool containsNonTrivialSubqusigroup() const;
        bool isQuadratical() const;
        bool isHexagonal() const;
        bool isGoldenSquare() const;
        bool isRightModular() const;
        bool isLeftModular() const;
        bool isAffineRegularOctagonal() const;
        bool isPentagonal() const;
        int findSubquasigroup(int border, unsigned int **a_sq) const;
        std::unordered_set<int> getGenerationSystem();

        friend std::ostream &operator<<(std::ostream &out, const Quasigroup &q);
    protected:
        int order;
        Quasigroup() = default;
    };

}

#endif //QUASIGROUP_QUASIGROUP_H
