#ifndef INCIDENCECUBE_H
#define INCIDENCECUBE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

namespace Quasigroup {

    /*
     * Класс кубов инцидентности, необходимый
     * для генерации квазигрупп Jacobson-Matthews методом
     */

    class IncidenceCube {
    public:
        explicit IncidenceCube(int size);
        ~IncidenceCube();
        void AddUnit(int x, int y, int z);
        bool isProper() const { return proper; }
        void setProper(bool newProper) { this->proper = newProper; }
        int getUnitXY(int x, int y) { return unitXY[x][y]; }
        int getUnitXZ(int x, int z) { return unitXZ[x][z]; }
        int getUnitYZ(int y, int z) { return unitYZ[y][z]; }
        friend std::ostream &operator<<(std::ostream &out, const IncidenceCube &cube);
    private:
        int size{};
        int **unitXY{};
        int **unitXZ{};
        int **unitYZ{};
        bool proper{};
        IncidenceCube() = default;;
    };

}

#endif // INCIDENCECUBE_H
