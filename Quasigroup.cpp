#include "Quasigroup.h"

Quasigroup::Quasigroup(int order)
{
    this->order = order;
    latin_square = new int*[order];
    for(int i = 0; i < order; i++)
        latin_square[i] = new int[order];

    if(order == 1)
        latin_square[0][0] = 0;
    else
        Generate();
}


Quasigroup::Quasigroup(int order, int square[])
{
    this->order = order;
    latin_square = new int*[order];
    for(int i = 0; i < order; i++)
        latin_square[i] = new int[order];

    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
            latin_square[i][j] = square[j + i * order];
    }
}


Quasigroup::~Quasigroup()
{
    for(int i = 0; i < order; i++)
        delete[] latin_square[i];
    delete [] latin_square;
}


void Quasigroup::Generate()
{
    IncidenceCube cube(order);
    int i = 0;

    int pickX;
    int pickY;
    int pickZ;

    int firstX;
    int firstY;
    int firstZ;

    int secondX;
    int secondY;
    int secondZ;

    int minusX;
    int minusY;
    int minusZ;

    while(i < order * order * order || !cube.proper)
    {
        if(cube.proper)
        {
            do
            {
                pickX = rand() % order;
                pickY = rand() % order;
                pickZ = rand() % order;
            } while (cube.unitXY[pickX][pickY] == pickZ);

            firstX = cube.unitYZ[pickY][pickZ];
            firstY = cube.unitXZ[pickX][pickZ];
            firstZ = cube.unitXY[pickX][pickY];

            cube.AddUnit(pickX, pickY, pickZ);
        }
        else
        {
            int randomBit;

            pickX = minusX;
            pickY = minusY;
            pickZ = minusZ;

            firstX = cube.unitYZ[pickY][pickZ];
            firstY = cube.unitXZ[pickX][pickZ];
            firstZ = cube.unitXY[pickX][pickY];

            randomBit = rand() % 2;
            if(randomBit)
                std::swap(firstX, secondX);

            randomBit = rand() % 2;
            if(randomBit)
                std::swap(firstY, secondY);

            randomBit = rand() % 2;
            if(randomBit)
                std::swap(firstZ, secondZ);

            cube.AddUnit(secondX, pickY, pickZ);
            cube.AddUnit(pickX, secondY, pickZ);
            cube.AddUnit(pickX, pickY, secondZ);
        }

        if(cube.unitXY[firstX][firstY] != firstZ)
        {
            cube.proper = false;

            minusX = firstX;
            minusY = firstY;
            minusZ = firstZ;

            secondX = cube.unitYZ[firstY][firstZ];
            secondY = cube.unitXZ[firstX][firstZ];
            secondZ = cube.unitXY[firstX][firstY];
        }
        else
        {
            cube.proper = true;
        }

        cube.AddUnit(pickX, firstY, firstZ);
        cube.AddUnit(firstX, pickY, firstZ);
        cube.AddUnit(firstX, firstY, pickZ);

        i++;
    }

    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
        {
            latin_square[i][j] = cube.unitXY[i][j];
        }
    }
}


bool Quasigroup::IsAffine()
{
    std::vector<int> tempMatrixL1(order * order);
    std::vector<int> tempMatrix(order * order);
    std::vector<int> firstLine(order);
    std::vector<int> reverseFirstLine(order);
    int alpha, beta;

    for(int i = 0; i < order; i++)
        firstLine[i] = latin_square[0][i];

    reverseFirstLine = GetReversePermutation(firstLine);

    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
            tempMatrixL1[j + i * order] = latin_square[i][reverseFirstLine[j]];
    }

    for(int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            tempMatrix[j + tempMatrixL1[i * order] * order] = tempMatrixL1[j + i * order];
        }
    }


    if(!IsSymmetricMatrix(tempMatrix))
        return false;


    for(int r = 0; r < order; r++)
    {
        for(int s = 0; s < order; s++)
        {
            for(int t = 0; t < order; t++)
            {
                if(tempMatrix[t + tempMatrix[s + r * order] * order] !=
                   tempMatrix[tempMatrix[t + s * order] + r * order])
                    return false;
            }
        }
    }


    for(int i = 0; i < order; i++)
    {
        if(latin_square[0][i] == tempMatrix[0])
        {
            alpha = i;
            break;
        }
    }

    for(int i = 0; i < order; i++)
    {
        if(latin_square[i][0] == tempMatrix[0])
        {
            beta = i;
            break;
        }
    }

    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
        {
            if(latin_square[tempMatrix[j + i * order]][alpha] !=
               tempMatrix[latin_square[j][alpha] + latin_square[i][alpha] * order] ||
               latin_square[beta][tempMatrix[j + i * order]] !=
               tempMatrix[latin_square[beta][j] + latin_square[beta][i] * order])
                return false;
        }
    }

    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
        {
            if(latin_square[i][j] !=
               tempMatrix[latin_square[0][0] + tempMatrix[latin_square[beta][j] + latin_square[i][alpha] * order] * order])
                return false;
        }
    }

    return true;
}


bool Quasigroup::IsSimple()
{
    int pairsCount = (order * (order - 1))/2;

    for(int j = 1; j < order; j++)
    {
        std::queue<UnorderedPair> unrevEq;
        std::vector<int> classes[order];
        int classIndex[order];
        int equalPairsCount = 0;
        int maxClassSize = 2;
        bool classMost = false;

        int a = 0, b = 0;

        for(int t = 0; t < order; t++)
        {
            classes[t].push_back(t);
            classIndex[t] = t;
        }

        MergeClasses(classes, classIndex, 0, j);
        equalPairsCount++;
        unrevEq.push({0, j});

        if(maxClassSize > order / 2)
            classMost = true;

        while(unrevEq.size() > 0 && !classMost)
        {
            a = unrevEq.front().firstElement;
            b = unrevEq.front().secondElement;
            unrevEq.pop();

            for(int i = 0; i < order; i++)
            {
                int sa_line, sb_line, sa_column, sb_column;

                sa_line = latin_square[i][a];
                sb_line = latin_square[i][b];
                sa_column = latin_square[a][i];
                sb_column = latin_square[b][i];

                if(classIndex[sa_line] != classIndex[sb_line])
                {
                    unrevEq.push({sa_line, sb_line});

                    equalPairsCount += (int)classes[classIndex[sa_line]].size() * (int)classes[classIndex[sb_line]].size();
                    int newClassSize = MergeClasses(classes, classIndex, classIndex[sa_line], classIndex[sb_line]);
                    if (newClassSize > maxClassSize)
                        maxClassSize = newClassSize;
                }

                if(classIndex[sa_column] != classIndex[sb_column])
                {
                    unrevEq.push({sa_column, sb_column});

                    equalPairsCount += (int)classes[classIndex[sa_column]].size() * (int)classes[classIndex[sb_column]].size();
                    int newClassSize = MergeClasses(classes, classIndex, classIndex[sa_column], classIndex[sb_column]);
                    if (newClassSize > maxClassSize)
                        maxClassSize = newClassSize;
                }

                if (maxClassSize > order / 2)
                {
                    classMost = true;
                    break;
                }
            }
        }

        if(equalPairsCount != pairsCount && !classMost)
            return false;
    }

    return true;
}


int Quasigroup::MergeClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass)
{
    if (fclass > sclass)
        std::swap(fclass, sclass);

    int startFClassSize = (int)classes[fclass].size();
    while(classes[sclass].size() > 0)
    {
        classes[fclass].push_back(classes[sclass][classes[sclass].size() - 1]);
        classIndex[classes[sclass][classes[sclass].size() - 1]] = fclass;
        classes[sclass].pop_back();
    }

    return (int)classes[fclass].size();
}


int Quasigroup::CalculateIndex(int t1, int t2)
{
    if(t2 < t1)
        std::swap(t2, t1);

    return t1 * order + t2 - ((t1 + 1) * (t1 + 2)) / 2;
}


std::vector<int> Quasigroup::GetReversePermutation(std::vector <int> permutation)
{
    std::vector<int> revPermutation(permutation.size());

    for(unsigned int i = 0; i < permutation.size(); i++)
        revPermutation[permutation[i]] = i;

    return revPermutation;
}


void Quasigroup::SwapLines(std::vector <int> &matrix, int i, int j)
{
    for(int k = 0; k < order; k++)
        std::swap(matrix[k + i * order] , matrix[k + j * order]);
}


bool Quasigroup::IsSymmetricMatrix(std::vector <int> matrix)
{
    for(int i = 0; i < order; i++)
    {
        for(int j = i + 1; j < order; j++)
        {
            if(matrix[j + i * order] != matrix[i + j * order])
                return false;
        }
    }
    return true;
}


std::ostream& operator<< (std::ostream &out, const Quasigroup &quasigroup)
{
    for(int i = 0; i < quasigroup.order; i++)
    {
        for(int j = 0; j < quasigroup.order; j++)
            out << quasigroup.latin_square[i][j] << " ";
        out << "\n";
    }
    return out;
}
