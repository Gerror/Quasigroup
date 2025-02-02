#include "DihedralGroup.h"

namespace Quasigroup {

    DihedralGroup::DihedralGroup(int order) : LatinSquareQuasigroup(order) {
        int halfOrder = order / 2;
        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                if (x < halfOrder && y < halfOrder) {
                    // R_i * R_j = R_{i+j}
                    latinSquare[x][y] = mod(x + y, halfOrder);
                } else if (x < halfOrder && y >= halfOrder) {
                    // R_i * S_j = S_{i+j}
                    latinSquare[x][y] = mod(y - halfOrder + x, halfOrder) + halfOrder;
                } else if (x >= halfOrder && y < halfOrder) {
                    // S_i * R_j = S_{i-j}
                    latinSquare[x][y] = mod(x - halfOrder - y, halfOrder) + halfOrder;
                } else {
                    // S_i * S_j = R_{i-j}
                    latinSquare[x][y] = mod(x - y, halfOrder);
                }
            }
        }
    }

}
