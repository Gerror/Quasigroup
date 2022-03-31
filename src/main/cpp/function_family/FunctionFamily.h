//
// Created by Gerror on 31.03.2022.
//

#ifndef QUASIGROUP_FUNCTIONFAMILY_H
#define QUASIGROUP_FUNCTIONFAMILY_H

#include <ostream>
#include <fstream>
#include <iostream>

namespace Quasigroup {

    class FunctionFamily {
    private:
        int numberOfFunctions;
        int functionSize;
    public:
        FunctionFamily(int k, int n, int numberOfFunctions, int functionSize);
        FunctionFamily(int k, int n, int numberOfFunctions, int functionSize, std::ifstream &input);
        FunctionFamily(const FunctionFamily &ff);
        FunctionFamily() = default;
        ~FunctionFamily();
        int getK() const;
        int getN() const;
        int getNumberOfFunctions() const;
        int getFunctionSize() const;
        int getFunctionValue(int varValue, int functionNumber = 0) const;
        friend std::ostream &operator<<(std::ostream &out, const FunctionFamily &ff);
        friend bool operator==(const FunctionFamily &ff1, const FunctionFamily &ff2);
        FunctionFamily &operator=(const FunctionFamily & ff);
    protected:
        int k;
        int n;
        int **functionFamily;
    };

}

#endif //QUASIGROUP_FUNCTIONFAMILY_H
