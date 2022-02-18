#ifndef QUASIGROUP_H
#define QUASIGROUP_H

#include <math.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <queue>
#include "IncidenceCube.h"

namespace Quasigroup {
    enum QuasigroupType {
        LATIN_SQUARE,
        PROPER_FAMILY
    };

    struct UnorderedPair {
        int firstElement;
        int secondElement;
    };

    class Quasigroup {
    private:
        int order; // == k^n if proper families
        int k; // k-logic
        int n; // proper families count
        unsigned long long int seed;

        std::random_device rd;
        std::mt19937 mersenne;

    public:
        QuasigroupType type;

        bool setLatinSquare;
        bool setProperFamily;

        int **latinSquare; // latin square - order * order
        int **properFamilies; // proper families - n * k^n

    private:
        Quasigroup() {}

        void GenerateProperFamilies(int stepCount);

        void GenerateLatinSquare();

        void DFS(int v, std::vector<int> (&edges)[], bool *used, std::vector<int> &comp);

        void IntValueToKArray(int value, int *kArray, int size);

        void SwapLines(std::vector<int> *matrix, int i, int j);

        bool IsSymmetricMatrix(std::vector<int> matrix);

        int KArrayToIntValue(int *kArray, int size);

        int UnarFunction(int x, int j);

        int Min(int a, int b);

        int Max(int a, int b);

        int CalculateIndex(int t1, int t2);

        int MergeClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass);

        std::vector<int> GetReversePermutation(std::vector<int> permutation);

    public:
        Quasigroup(int order, int seed = 0);

        Quasigroup(int order, int latinSquare[]);

        Quasigroup(int k, int n, int properFamilies[], bool needLatinSquare = false);

        Quasigroup(int k, int n, bool needLatinSquare = false, int seed = 0);

        Quasigroup(std::string filename, QuasigroupType format);

        Quasigroup(const Quasigroup &q);

        ~Quasigroup();

        bool IsAffine();

        bool IsSimple();

        bool TrueLatinSquare();

        bool TrueProperFamily();

        bool ContainsConstantFunction();

        void ProperFamiliesToLatinSquare(int *pi_value = NULL);

        void PrintToFile(std::string filename, QuasigroupType format);

        unsigned long long int GetSeed() { return seed; }

        friend std::ostream &operator<<(std::ostream &out, const Quasigroup &quasigroup);

        friend bool operator==(const Quasigroup &q1, const Quasigroup &q2);
    };
}

#endif // QUASIGROUP_H
