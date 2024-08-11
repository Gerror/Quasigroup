#ifndef QUASIGROUP_LATINSQUAREQUASIGROUP_H
#define QUASIGROUP_LATINSQUAREQUASIGROUP_H

#include <fstream>
#include <functional>

#include "Quasigroup.h"
#include "FunctionalQuasigroup.h"

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
        LatinSquareQuasigroup(std::initializer_list<std::initializer_list<int>> latinSquare);
        LatinSquareQuasigroup(int order, std::function<int(int, int)> product);
        explicit LatinSquareQuasigroup(const FunctionalQuasigroup& functionalQuasigroup);
        ~LatinSquareQuasigroup();
        friend bool operator==(const LatinSquareQuasigroup &q1, const LatinSquareQuasigroup &q2);
        void swapRows(int firstLineNumber, int secondLineNumber);
    protected:
        int **latinSquare;
    };

}

#endif //QUASIGROUP_LATINSQUAREQUASIGROUP_H
