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

    LatinSquareQuasigroup::LatinSquareQuasigroup(std::initializer_list<std::initializer_list<int>> latinSquare)
            : LatinSquareQuasigroup(latinSquare.size()) {
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

    LatinSquareQuasigroup::LatinSquareQuasigroup(const Quasigroup &q)
            : LatinSquareQuasigroup(q.getOrder()) {
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                this->latinSquare[x][y] = q.getProduct(x, y);
            }
        }
    }

    LatinSquareQuasigroup::LatinSquareQuasigroup(int order, const std::function<int(int, int)> &product)
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

    void LatinSquareQuasigroup::swapColumns(int firstColumnNumber, int secondColumnNumber) {
        for (int i = 0; i < order; i++) {
            std::swap(latinSquare[i][firstColumnNumber], latinSquare[i][secondColumnNumber]);
        }
    }

    void LatinSquareQuasigroup::setRow(int rowNumber, const std::vector<int> &values) {
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (latinSquare[rowNumber][j] == values[i]) {
                    swapColumns(i, j);
                    break;
                }
            }
        }
    }

    void LatinSquareQuasigroup::setColumn(int columnNumber, const std::vector<int> &values) {
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (latinSquare[j][columnNumber] == values[i]) {
                    swapRows(i, j);
                    break;
                }
            }
        }
    }

}