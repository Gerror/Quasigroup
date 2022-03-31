//
// Created by Gerror on 31.03.2022.
//

#include <iostream>
#include "FunctionFamily.h"

namespace Quasigroup {

    FunctionFamily::FunctionFamily(int k, int n, int numberOfFunctions, int functionSize) {
        this->k = k;
        this->n = n;
        this->numberOfFunctions = numberOfFunctions;
        this->functionSize = functionSize;

        functionFamily = new int *[numberOfFunctions];
        for (int i = 0; i < numberOfFunctions; i++) {
            functionFamily[i] = new int[functionSize];
        }
    }

    FunctionFamily::FunctionFamily(const FunctionFamily &ff) : FunctionFamily(ff.k, ff.n, ff.numberOfFunctions, ff.functionSize) {
        for (int i = 0; i < ff.numberOfFunctions; i++) {
            for (int j = 0; j < ff.functionSize; j++) {
                this->functionFamily[i][j] = ff.functionFamily[i][j];
            }
        }
    }

    FunctionFamily::FunctionFamily(int k, int n, int numberOfFunctions, int functionSize, std::ifstream &input) :
    FunctionFamily(k, n, numberOfFunctions, functionSize) {
        for (int i = 0; i < numberOfFunctions; i++) {
            for (int j = 0; j < functionSize; j++) {
                input >> functionFamily[i][j];
            }
        }
    }

    FunctionFamily::~FunctionFamily() {
        for (int i = 0; i < numberOfFunctions; i++) {
            delete[] (functionFamily[i]);
        }
        delete[] (functionFamily);
    }

    int FunctionFamily::getK() const {
        return k;
    }

    int FunctionFamily::getN() const {
        return n;
    }

    int FunctionFamily::getFunctionValue(int varValue, int functionNumber) const {
        return functionFamily[functionNumber][varValue];
    }

    int FunctionFamily::getNumberOfFunctions() const {
        return numberOfFunctions;
    }

    int FunctionFamily::getFunctionSize() const {
        return functionSize;
    }

    std::ostream &operator<<(std::ostream &out, const FunctionFamily &ff) {
        for (int functionNumber = 0; functionNumber < ff.getNumberOfFunctions(); functionNumber++) {
            for (int arg = 0; arg < ff.getFunctionSize(); arg++) {
                out << ff.getFunctionValue(arg, functionNumber) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    bool operator==(const FunctionFamily &ff1, const FunctionFamily &ff2) {
        if (ff1.getNumberOfFunctions() != ff2.getNumberOfFunctions() || ff1.getFunctionSize() != ff2.getFunctionSize()) {
            return false;
        }

        int numberOfFunctions = ff1.getNumberOfFunctions();
        int functionSize = ff1.getFunctionSize();

        for (int functionNumber = 0; functionNumber < numberOfFunctions; functionNumber++) {
            for (int arg = 0; arg < functionSize; arg++) {
                if (ff1.getFunctionValue(arg, functionNumber) != ff2.getFunctionValue(arg, functionNumber)) {
                    return false;
                }
            }
        }

        return true;
    }

    FunctionFamily &FunctionFamily::operator=(const FunctionFamily &ff) {
        if (this != &ff) {
            this->k = ff.k;
            this->n = ff.n;
            this->numberOfFunctions = ff.numberOfFunctions;
            this->functionSize = ff.functionSize;

            functionFamily = new int *[numberOfFunctions];
            for (int i = 0; i < numberOfFunctions; i++) {
                functionFamily[i] = new int[functionSize];
            }

            for (int i = 0; i < ff.numberOfFunctions; i++) {
                for (int j = 0; j < ff.functionSize; j++) {
                    this->functionFamily[i][j] = ff.functionFamily[i][j];
                }
            }
        }
        return *this;
    }

}
