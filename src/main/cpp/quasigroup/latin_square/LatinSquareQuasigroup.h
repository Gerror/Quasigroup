//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_LATINSQUAREQUASIGROUP_H
#define QUASIGROUP_LATINSQUAREQUASIGROUP_H

#include <fstream>

#include "Quasigroup.h"

namespace Quasigroup {

    /*
     * The class of quasigroups defined by the Latin square
     */

    class LatinSquareQuasigroup : public Quasigroup {
    public:
        int getProduct(int x, int y) const override;
        explicit LatinSquareQuasigroup(int order);
        LatinSquareQuasigroup(int order, std::ifstream &input);
        LatinSquareQuasigroup(int order, int **latinSquare);
        ~LatinSquareQuasigroup();
        friend bool operator==(const LatinSquareQuasigroup &q1, const LatinSquareQuasigroup &q2);
    protected:
        int **latinSquare;
    };

}

#endif //QUASIGROUP_LATINSQUAREQUASIGROUP_H
