#ifndef QUASIGROUP_H
#define QUASIGROUP_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <queue>
#include <ctime>
#include "IncidenceCube.h"

struct UnorderedPair
{
    int firstElement;
    int secondElement;
};

class Quasigroup
{
    public:
        Quasigroup(int order);
        Quasigroup(int order, int square[]);

        ~Quasigroup();

        bool IsAffine();
        bool IsSimple();

        friend std::ostream& operator<< (std::ostream &out, const Quasigroup &quasigroup);

    protected:

    private:
        int order;
        int** latin_square;

        Quasigroup() {}

        void Generate();

        int CalculateIndex(int t1, int t2);
        std::vector<int> GetReversePermutation(std::vector <int> permutation);
        void SwapLines(std::vector <int> &matrix, int i, int j);
        bool IsSymmetricMatrix(std::vector <int> matrix);

        int MergeClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass);
};

#endif // QUASIGROUP_H
