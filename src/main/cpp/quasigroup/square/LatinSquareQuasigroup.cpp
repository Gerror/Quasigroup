#include "LatinSquareQuasigroup.h"

namespace Quasigroup {

    int LatinSquareQuasigroup::getProduct(int x, int y) const {
        return latinSquare[x][y];
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(int order) {
        this->order = order;

        latinSquare = new int *[order];
        for (int i = 0; i < order; i++) {
            latinSquare[i] = new int[order];
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(int order, std::ifstream &input) : LatinSquareQuasigroup(order) {
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                input >> latinSquare[x][y];
            }
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(int order, int **latinSquare) : LatinSquareQuasigroup(order) {
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                this->latinSquare[x][y] = latinSquare[x][y];
            }
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(std::initializer_list<std::initializer_list<int>> latinSquare) : LatinSquareQuasigroup(latinSquare.size()) {
        int i = 0;
        for (auto row : latinSquare) {
            int j = 0;
            for (auto element : row) {
                this->latinSquare[i][j] = element;
                j++;
            }
            i++;
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(const FunctionalQuasigroup& functionalQuasigroup)
    : LatinSquareQuasigroup(functionalQuasigroup.getOrder()) {
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                this->latinSquare[x][y] = functionalQuasigroup.getProduct(x, y);
            }
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(int order, std::function<int(int, int)> product)
    : LatinSquareQuasigroup(order) {
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                this->latinSquare[x][y] = product(x, y);
            }
        }
    }

    LatinSquareQuasigroup::~LatinSquareQuasigroup() {
        for (int i = 0; i < order; i++) {
            delete[] (latinSquare[i]);
        }
        delete[] (latinSquare);
    }

    bool operator==(const LatinSquareQuasigroup &q1, const LatinSquareQuasigroup &q2) {
        if (q1.order != q2.order) {
            return false;
        }

        int order = q1.order;

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (q1.getProduct(i, j) != q2.getProduct(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

    void LatinSquareQuasigroup::swapRows(int firstLineNumber, int secondLineNumber) {
        for (int i = 0; i < order; i++) {
            std::swap(latinSquare[firstLineNumber][i], latinSquare[secondLineNumber][i]);
        }
    }

}