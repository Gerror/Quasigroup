#ifndef INCIDENCECUBE_H
#define INCIDENCECUBE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

namespace Quasigroup {

    /*
     * Incidence cube class required to generate
     * Jacobson-Matthews quasigroups by the method
     */

    class IncidenceCube {
    public:
        explicit IncidenceCube(int size);
        ~IncidenceCube();
        void AddUnit(int x, int y, int z);
        bool isProper() const;
        void setProper(bool newProper);
        int getUnitXY(int x, int y);
        int getUnitXZ(int x, int z);
        int getUnitYZ(int y, int z);
        friend std::ostream &operator<<(std::ostream &out, const IncidenceCube &cube);
    private:
        int size;
        int **unitXY;
        int **unitXZ;
        int **unitYZ;
        bool proper;
        IncidenceCube() = default;;
    };

}

#endif // INCIDENCECUBE_H
