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
        IncidenceCube cube(order);
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

        while (i < order * order * order || !cube.isProper()) {
            if (cube.isProper()) {
                do {
                    pickX = mersenne() % order;
                    pickY = mersenne() % order;
                    pickZ = mersenne() % order;
                } while (cube.getUnitXY(pickX, pickY) == pickZ);

                firstX = cube.getUnitYZ(pickY, pickZ);
                firstY = cube.getUnitXZ(pickX, pickZ);
                firstZ = cube.getUnitXZ(pickX, pickY);

                cube.AddUnit(pickX, pickY, pickZ);
            } else {
                int randomBit;

                pickX = minusX;
                pickY = minusY;
                pickZ = minusZ;

                firstX = cube.getUnitYZ(pickY, pickZ);
                firstY = cube.getUnitXZ(pickX, pickZ);
                firstZ = cube.getUnitXY(pickX, pickY);

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

            if (cube.getUnitXY(firstX, firstY) != firstZ) {
                cube.setProper(false);

                minusX = firstX;
                minusY = firstY;
                minusZ = firstZ;

                secondX = cube.getUnitYZ(firstY, firstZ);
                secondY = cube.getUnitXZ(firstX, firstZ);
                secondZ = cube.getUnitXY(firstX, firstY);
            } else {
                cube.setProper(true);
            }

            cube.AddUnit(pickX, firstY, firstZ);
            cube.AddUnit(firstX, pickY, firstZ);
            cube.AddUnit(firstX, firstY, pickZ);

            i++;
        }

        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                latinSquare[x][y] = cube.getUnitXY(x, y);
            }
        }
    }

}
