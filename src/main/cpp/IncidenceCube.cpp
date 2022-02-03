#include "IncidenceCube.h"

namespace IncidenceCube
{
    IncidenceCube::IncidenceCube(int size)
    {
        this->size = size;

        unitXY = new int*[size];
        unitXZ = new int*[size];
        unitYZ = new int*[size];
        for(int i = 0; i < size; i++)
        {
            unitXY[i] = new int[size];
            unitXZ[i] = new int[size];
            unitYZ[i] = new int[size];
        }

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                int k = (i + j) % size;
                unitXY[i][j] = k;
                unitXZ[i][k] = j;
                unitYZ[j][k] = i;
            }
        }

        proper = true;
    }

    IncidenceCube::~IncidenceCube()
    {
        for(int i = 0; i < size; i++)
        {
            delete[] unitXY[i];
            delete[] unitXZ[i];
            delete[] unitYZ[i];
        }
        delete[] unitXY;
        delete[] unitXZ;
        delete[] unitYZ;
    }


    void IncidenceCube::AddUnit(int x, int y, int z)
    {
        unitXY[x][y] = z;
        unitYZ[y][z] = x;
        unitXZ[x][z] = y;
    }


    std::ostream& operator<< (std::ostream &out, const IncidenceCube &cube)
    {
        for(int i = 0; i < cube.size; i++)
        {
            for(int j = 0; j < cube.size; j++)
            {
                for(int k = 0; k < cube.size; k++)
                {
                    if (cube.unitXY[i][j] == k)
                        out << 1 << " ";
                    else
                        out << 0 << " ";
                }

                out << " ";
            }
            out << "\n";
        }
        return out;
    }
}
