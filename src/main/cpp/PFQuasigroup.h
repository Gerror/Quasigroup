//
// Created by rzhig on 05.03.2022.
//

#ifndef QUASIGROUP_PFQUASIGROUP_H
#define QUASIGROUP_PFQUASIGROUP_H

#define STEP_COUNT order * order

#include <iostream>
#include <fstream>

#include "Quasigroup.h"
#include "ProperFamily.h"

namespace Quasigroup {

    /*
     * Квазигруппы, порождаемые правильными семействами функций
     */

    class PFQuasigroup : public Quasigroup {
    private:
        int k;
        int n;
        ProperFamily properFamily;
        int *piValue{};
    public:
        int getProduct(int x, int y) const override;
        PFQuasigroup(const ProperFamily& properFamily, unsigned long long int seed);
        PFQuasigroup(int k, int n, unsigned long long int seed) : PFQuasigroup(ProperFamily(k, n), seed) {}
        PFQuasigroup(int k, int n) : PFQuasigroup(k, n, time(nullptr)) {};
        explicit PFQuasigroup(const ProperFamily& properFamily) : PFQuasigroup(properFamily, time(nullptr)) {}
        ~PFQuasigroup();
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_PFQUASIGROUP_H
