#ifndef INCIDENCECUBE_H
#define INCIDENCECUBE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

namespace IncidenceCube {
    class IncidenceCube {
    public:
        int **unitXY;
        int **unitXZ;
        int **unitYZ;

        void AddUnit(int x, int y, int z);

        bool proper;

        IncidenceCube(int size);

        ~IncidenceCube();

        friend std::ostream &operator<<(std::ostream &out, const IncidenceCube &cube);

    protected:

    private:
        int size;

        IncidenceCube() {};
    };
}

#endif // INCIDENCECUBE_H
