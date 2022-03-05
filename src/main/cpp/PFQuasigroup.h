//
// Created by rzhig on 05.03.2022.
//

#ifndef QUASIGROUP_PFQUASIGROUP_H
#define QUASIGROUP_PFQUASIGROUP_H

#define STEP_COUNT order * order

#include <iostream>
#include <fstream>

#include "Quasigroup.h"

namespace Quasigroup {

    class PFQuasigroup : public Quasigroup {
    private:
        int k;
        int n;
        int **properFamilies;
        int *piValue;
        void generatePiValue();
    public:
        int getProduct(int x, int y) const override;
        int getK();
        int getN();
        PFQuasigroup(int k, int n, unsigned long long int seed);
        PFQuasigroup(int k, int n) : PFQuasigroup(k, n, time(nullptr)) {}
        PFQuasigroup(std::ifstream &input);
        friend std::ostream &operator<<(std::ostream &out, const PFQuasigroup &quasigroup);
        friend bool operator==(const PFQuasigroup &q1, const PFQuasigroup &q2);
        ~PFQuasigroup();
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_PFQUASIGROUP_H
