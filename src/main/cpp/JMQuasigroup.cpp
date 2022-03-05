//
// Created by rzhig on 04.03.2022.
//

#include "JMQuasigroup.h"

namespace  Quasigroup {

    JMQuasigroup::JMQuasigroup(std::ifstream &input) {
        if (!input.is_open()) {
            std::cerr << "Input JMQuasigroup from ifstream, but ifstream was not open" << std::endl;
            return;
        }

        input >> order;

        latinSquare = new int *[order];
        for (int i = 0; i < order; i++) {
            latinSquare[i] = new int[order];
        }

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                input >> latinSquare[i][j];
            }
        }
    }

    JMQuasigroup::JMQuasigroup(int order, unsigned long long int seed) {
        this->order = order;
        this->seed = seed;
        this->mersenne = std::mt19937(seed);

        latinSquare = new int *[order];
        for (int i = 0; i < order; i++) {
            latinSquare[i] = new int[order];
        }

        if (order == 1) {
            latinSquare[0][0] = 0;
        }
        else {
            generate();
        }
    }

    JMQuasigroup::~JMQuasigroup() {
        for (int i = 0; i < order; i++) {
            delete[] (latinSquare[i]);
        }
        delete[] (latinSquare);
    }

    void JMQuasigroup::generate() {
        IncidenceCube::IncidenceCube cube(order);
        int i = 0;

        // pick point coord
        int pickX;
        int pickY;
        int pickZ;

        // first 1 coord
        int firstX;
        int firstY;
        int firstZ;

        // second 1 coord
        int secondX;
        int secondY;
        int secondZ;

        // -1 coord
        int minusX;
        int minusY;
        int minusZ;

        while (i < order * order * order || !cube.proper) {
            if (cube.proper) {
                do {
                    pickX = mersenne() % order;
                    pickY = mersenne() % order;
                    pickZ = mersenne() % order;
                } while (cube.unitXY[pickX][pickY] == pickZ);

                firstX = cube.unitYZ[pickY][pickZ];
                firstY = cube.unitXZ[pickX][pickZ];
                firstZ = cube.unitXY[pickX][pickY];

                cube.AddUnit(pickX, pickY, pickZ);
            } else {
                int randomBit;

                pickX = minusX;
                pickY = minusY;
                pickZ = minusZ;

                firstX = cube.unitYZ[pickY][pickZ];
                firstY = cube.unitXZ[pickX][pickZ];
                firstZ = cube.unitXY[pickX][pickY];

                randomBit = mersenne() % 2;
                if (randomBit)
                    std::swap(firstX, secondX);

                randomBit = mersenne() % 2;
                if (randomBit)
                    std::swap(firstY, secondY);

                randomBit = mersenne() % 2;
                if (randomBit)
                    std::swap(firstZ, secondZ);

                cube.AddUnit(secondX, pickY, pickZ);
                cube.AddUnit(pickX, secondY, pickZ);
                cube.AddUnit(pickX, pickY, secondZ);
            }

            if (cube.unitXY[firstX][firstY] != firstZ) {
                cube.proper = false;

                minusX = firstX;
                minusY = firstY;
                minusZ = firstZ;

                secondX = cube.unitYZ[firstY][firstZ];
                secondY = cube.unitXZ[firstX][firstZ];
                secondZ = cube.unitXY[firstX][firstY];
            } else {
                cube.proper = true;
            }

            cube.AddUnit(pickX, firstY, firstZ);
            cube.AddUnit(firstX, pickY, firstZ);
            cube.AddUnit(firstX, firstY, pickZ);

            i++;
        }

        for (int j = 0; j < order; j++) {
            for (int k = 0; k < order; k++) {
                latinSquare[j][k] = cube.unitXY[j][k];
            }
        }
    }

    int JMQuasigroup::getProduct(int x, int y) const {
        return latinSquare[x][y];
    }

    std::ostream &operator<<(std::ostream &out, const JMQuasigroup &quasigroup) {
        return quasigroup.putLatinSquare(out);
    }

    bool operator==(const JMQuasigroup &q1, const JMQuasigroup &q2) {
        if (q1.order != q2.order) {
            return false;
        }

        int order = q1.order;

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (q1.latinSquare[i][j] != q2.latinSquare[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

}
