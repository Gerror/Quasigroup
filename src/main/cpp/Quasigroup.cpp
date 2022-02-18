#include "Quasigroup.h"

namespace Quasigroup {
    // Proper families constructor
    Quasigroup::Quasigroup(int k, int n, bool needLatinSquare, int seed) {
        this->k = k;
        this->n = n;
        order = pow(k, n);
        latinSquare = NULL;
        properFamilies = NULL;
        setProperFamily = false;
        setLatinSquare = false;
        type = PROPER_FAMILY;

        properFamilies = new int *[n];
        for (int i = 0; i < n; i++) {
            properFamilies[i] = new int[order];
        }

        if (seed == 0)
            this->seed = rd();
        else
            this->seed = seed;
        mersenne = std::mt19937(this->seed);

        GenerateProperFamilies(order * order);

        if (needLatinSquare) {
            latinSquare = new int *[order];
            for (int i = 0; i < order; i++) {
                latinSquare[i] = new int[order];
            }

            ProperFamiliesToLatinSquare();
        }
    }

    //Quasigroup from file
    Quasigroup::Quasigroup(std::string filename, QuasigroupType format) {
        std::ifstream in(filename.c_str());
        latinSquare = NULL;
        properFamilies = NULL;
        setProperFamily = false;
        setLatinSquare = false;
        seed = 0;

        if (format == LATIN_SQUARE) {
            in >> order;

            latinSquare = new int *[order];
            for (int i = 0; i < order; i++) {
                latinSquare[i] = new int[order];
            }

            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++)
                    in >> latinSquare[i][j];
            }

            type = LATIN_SQUARE;
            setLatinSquare = true;
        } else if (format == PROPER_FAMILY) {
            in >> k >> n;
            order = pow(k, n);

            properFamilies = new int *[n];
            for (int i = 0; i < n; i++) {
                properFamilies[i] = new int[order];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < order; j++)
                    in >> properFamilies[i][j];
            }

            type = PROPER_FAMILY;
            setProperFamily = true;
        }
        in.close();
    }

    // Jacobson-Matthew generate
    Quasigroup::Quasigroup(int order, int seed) {
        this->order = order;
        latinSquare = NULL;
        properFamilies = NULL;
        setProperFamily = false;
        setLatinSquare = false;
        type = LATIN_SQUARE;

        latinSquare = new int *[order];
        for (int i = 0; i < order; i++) {
            latinSquare[i] = new int[order];
        }

        if (seed == 0)
            this->seed = rd();
        else
            this->seed = seed;
        mersenne = std::mt19937(this->seed);

        if (order == 1)
            latinSquare[0][0] = 0;
        else
            GenerateLatinSquare();
    }

    // from latin square
    Quasigroup::Quasigroup(int order, int latinSquare[]) {
        this->order = order;
        latinSquare = NULL;
        properFamilies = NULL;
        setProperFamily = false;
        type = LATIN_SQUARE;
        seed = 0;

        this->latinSquare = new int *[order];
        for (int i = 0; i < order; i++) {
            this->latinSquare[i] = new int[order];
        }

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++)
                this->latinSquare[i][j] = latinSquare[j + i * order];
        }
        setLatinSquare = true;
    }

    Quasigroup::Quasigroup(int k, int n, int properFamilies[], bool needLatinSquare) {
        this->k = k;
        this->n = n;
        order = pow(k, n);
        latinSquare = NULL;
        this->properFamilies = NULL;
        setLatinSquare = false;
        type = PROPER_FAMILY;
        seed = 0;

        this->properFamilies = new int *[n];
        for (int i = 0; i < n; i++) {
            this->properFamilies[i] = new int[order];
            for (int j = 0; j < order; j++)
                this->properFamilies[i][j] = properFamilies[i * order + j];
        }
        setProperFamily = true;

        if (needLatinSquare) {
            latinSquare = new int *[order];
            for (int i = 0; i < order; i++) {
                latinSquare[i] = new int[order];
            }

            ProperFamiliesToLatinSquare();
        }
    }

    Quasigroup::Quasigroup(const Quasigroup &q) {
        this->k = q.k;
        this->n = q.n;
        this->order = q.order;
        this->seed = q.seed;
        this->type = q.type;
        latinSquare = NULL;
        properFamilies = NULL;

        if (q.setLatinSquare) {
            this->latinSquare = new int *[order];
            for (int i = 0; i < order; i++) {
                this->latinSquare[i] = new int[order];
                for (int j = 0; j < order; j++)
                    this->latinSquare[i][j] = q.latinSquare[i][j];
            }

            setLatinSquare = true;
        }
        if (q.setProperFamily) {
            this->properFamilies = new int *[n];
            for (int i = 0; i < n; i++) {
                this->properFamilies[i] = new int[order];
                for (int j = 0; j < order; j++)
                    this->properFamilies[i][j] = q.properFamilies[i][j];
            }
            setProperFamily = true;
        }
    }

    Quasigroup::~Quasigroup() {
        if (latinSquare != NULL) {
            for (int i = 0; i < order; i++) {
                if (latinSquare[i][0])
                    delete[] (latinSquare[i]);
            }
            delete[] (latinSquare);
        }

        if (properFamilies != NULL) {
            for (int i = 0; i < n; i++) {
                if (properFamilies[i][0])
                    delete[] (properFamilies[i]);
            }
            delete[] (properFamilies);
        }
    }

    void Quasigroup::GenerateProperFamilies(int stepCount) {
        // Create default proper families
        for (int i = 0; i < n; i++) {
            int value = mersenne() % k;
            for (int j = 0; j < order; j++)
                properFamilies[i][j] = value;
        }

        for (int i = 0; i < stepCount; i++) {
            // algorithm step

            // generate variable number
            int number = mersenne() % n;

            // Поменять местами переменную number с последней
            int newProperFamily[n][order];
            for (int j = 0; j < n; j++) {
                for (int m = 0; m < order; m++) {
                    int kArray[n];
                    IntValueToKArray(m, kArray, n);

                    int temp = kArray[number];
                    kArray[number] = kArray[n - 1];
                    kArray[n - 1] = temp;

                    newProperFamily[j][m] = properFamilies[j][KArrayToIntValue(kArray, n)];
                }
            }
            // Поменять местами функцию number с последней
            for (int j = 0; j < order; j++) {
                int temp = newProperFamily[number][j];
                newProperFamily[number][j] = newProperFamily[n - 1][j];
                newProperFamily[n - 1][j] = temp;
            }

            // Вернуть семейство как было
            for (int j = 0; j < n; j++) {
                for (int m = 0; m < order; m++) {
                    properFamilies[j][m] = newProperFamily[j][m];
                }
            }
            number = n - 1; // ???

            // new k proper families, n - 1 function, n - 1 variables
            int size = pow(k, n - 1);
            int G[k][n - 1][size];
            for (int j = 0; j < k; j++) {
                for (int m = 0; m < n - 1; m++) {
                    for (int p = 0; p < size; p++) {
                        int kArray[n];
                        int newkArray[n - 1];
                        IntValueToKArray(p, newkArray, n - 1);

                        kArray[n - 1] = j;
                        for (int q = 0; q < n - 1; q++)
                            kArray[q] = newkArray[q];

                        G[j][m][p] = properFamilies[m][KArrayToIntValue(kArray, n)];
                    }
                }
            }

            // Create n - 1 function in new proper families. (Formula (2))
            for (int j = 0; j < n - 1; j++) {
                for (int m = 0; m < order; m++) {
                    int kArray[n];
                    int newkArray[n - 1];
                    IntValueToKArray(m, kArray, n);

                    for (int q = 0; q < n - 1; q++)
                        newkArray[q] = kArray[q];

                    int newValue = KArrayToIntValue(newkArray, n - 1);

                    int result = 0;
                    for (int p = 0; p < k; p++)
                        result = Max(result, Min(UnarFunction(kArray[n - 1], p), G[p][j][newValue]));

                    properFamilies[j][m] = result;
                }
            }

            // Create graph
            std::vector<int> edges[size];
            bool used[size];
            for (int s = 0; s < size; s++) {
                used[s] = false;
                for (int t = s + 1; t < size; t++) {
                    int sArray[n - 1];
                    int tArray[n - 1];
                    IntValueToKArray(s, sArray, n - 1);
                    IntValueToKArray(t, tArray, n - 1);

                    // find pair G_{m}, G_{p}
                    bool needEdge = false;
                    for (int m = 0; m < k; m++) {
                        for (int p = m + 1; p < k; p++) {
                            bool isTruePair = true;
                            for (int j = 0; j < n - 1; j++) {
                                if (tArray[j] != sArray[j]) {
                                    if (G[m][j][t] == G[p][j][s])
                                        isTruePair = false;
                                }
                            }
                            if (isTruePair)
                                needEdge = true;
                        }
                    }

                    if (needEdge) {
                        edges[t].push_back(s);
                        edges[s].push_back(t);
                    }
                }
            }

            //calculate components and set value for last function
            std::vector<int> comp;
            for (int j = 0; j < size; j++) {
                if (!used[j]) {
                    comp.clear();
                    DFS(j, reinterpret_cast<std::vector<int> (&)[]>(edges), used, comp);

                    int value = mersenne() % k;
                    for (size_t m = 0; m < comp.size(); m++) {
                        for (int p = 0; p < k; p++)
                            properFamilies[n - 1][comp[m] * k + p] = value;
                    }
                }
            }
        }

        setProperFamily = true;
    }


    void Quasigroup::DFS(int v, std::vector<int> (&edges)[], bool *used, std::vector<int> &comp) {
        used[v] = true;
        comp.push_back(v);
        for (size_t i = 0; i < edges[v].size(); ++i) {
            int to = edges[v][i];
            if (!used[to])
                DFS(to, edges, used, comp);
        }
    }


    void Quasigroup::ProperFamiliesToLatinSquare(int *pi_value) {
        if (latinSquare == NULL) {
            latinSquare = new int *[order];
            for (int i = 0; i < order; i++) {
                latinSquare[i] = new int[order];
            }
        }

        bool allocMemory = false;
        if (pi_value == NULL) {
            pi_value = new int[n * k * k];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < k; j++) {
                    for (int m = 0; m < k; m++)
                        pi_value[i * k * k + j * k + m] = mersenne() % k;
                }
            }
            allocMemory = true;
        }

        for (int y = 0; y < order; y++) {
            for (int x = 0; x < order; x++) {
                int qArray[n];
                int xArray[n];
                int yArray[n];
                int pi[n];
                IntValueToKArray(x, xArray, n);
                IntValueToKArray(y, yArray, n);

                for (int m = 0; m < n; m++)
                    pi[m] = pi_value[m * k * k + xArray[m] * k + yArray[m]];

                for (int m = 0; m < n; m++) {
                    qArray[m] = xArray[m] + yArray[m] + properFamilies[m][KArrayToIntValue(pi, n)];
                    qArray[m] = qArray[m] % k;
                }
                latinSquare[x][y] = KArrayToIntValue(qArray, n);
            }
        }
        setLatinSquare = true;

        if (allocMemory)
            delete[] pi_value;
    }


    void Quasigroup::IntValueToKArray(int value, int *kArray, int size) {
        if (value > order - 1)
            std::cout << "[ERROR]: Bad value for convert to k-array\n";

        for (int i = 0; i < size; i++) {
            kArray[size - 1 - i] = value % k;
            value /= k;
        }
    }


    int Quasigroup::KArrayToIntValue(int *kArray, int size) {
        int result = 0;
        for (int i = 0; i < size; i++)
            result += kArray[i] * pow(k, size - 1 - i);
        return result;
    }


    int Quasigroup::UnarFunction(int x, int j) {
        if (x % k == j % k)
            return k - 1;
        return 0;
    }


    int Quasigroup::Min(int a, int b) {
        if (a % k < b % k)
            return a;
        return b;
    }


    int Quasigroup::Max(int a, int b) {

        if (a % k > b % k)
            return a;
        return b;
    }

    void Quasigroup::GenerateLatinSquare() {
        IncidenceCube::IncidenceCube cube(order);
        int i = 0;

        // pick point coord
        int pickX;
        int pickY;
        int pickZ;

        // if cube is not proper {{{
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
        // if cube is not proper }}}

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

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                latinSquare[i][j] = cube.unitXY[i][j];
            }
        }

        setLatinSquare = true;
    }

    bool Quasigroup::IsAffine() {
        if (!setLatinSquare) {
            if (setProperFamily)
                ProperFamiliesToLatinSquare();
            else {
                //std::cout << "[WARN]: Call IsAffine, but quasigroup is not set\n";
                return false;
            }
        }

        /*
        latinSquare далее - матрица L, её i-я строка - s(i)

        (1)
        По матрице L строим матрицу L' (tempMatrix), в которой при каждом i = 1, ..., order
        строка с номером i содержит перестановку s(i) * (s(1))^-1
        */

        std::vector<int> tempMatrix(order * order);
        std::vector<int> firstLine(order);
        std::vector<int> reverseFirstLine(order);
        int alpha, beta;

        for (int i = 0; i < order; i++)
            firstLine[i] = latinSquare[0][i];

        reverseFirstLine = GetReversePermutation(firstLine);

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++)
                tempMatrix[j + i * order] = latinSquare[i][reverseFirstLine[j]];
        }

        /*
        (2)
        По матрице L' (tempMatrix) строим матрицу L'', полученную из L' перестановкой строк,
        строк, такой что первый столбец L'' совпадает с первой строкой
        Далее операция, порожденная матрицей L'' будем обозначать f''
        (L'' хранится так же в tempMatrix)
        */

        for (int i = 1; i < order; i++)
            SwapLines(&tempMatrix, i, tempMatrix[i * order]);

        /*
        (3)
        Проверяем симметричность L'' (коммутативность f'')
        Если не симметрична, то неудача
        */

        if (!IsSymmetricMatrix(tempMatrix))
            return false;

        /*
        (4)
        Проверяем ассоциативность f'', т.е. для всех r,s,t,
        1 <= r,s,t <= order
        f''(f''(qr, qs), qt) == f''(qr, f''(qs, qt))
        Если не ассоциативна, то неудача
        */

        for (int r = 0; r < order; r++) {
            for (int s = 0; s < order; s++) {
                for (int t = 0; t < order; t++) {
                    if (tempMatrix[t + tempMatrix[s + r * order] * order] !=
                        tempMatrix[tempMatrix[t + s * order] + r * order])
                        return false;
                }
            }
        }

        /*
        (5)
        Рассматриваем столбец матрицы L,первый элемент которого
        совпадает с левым верхним элементом L''
        Обозначаем заданную этим столбцем перестановку (номер столбца) за alpha
        */

        for (int i = 0; i < order; i++) {
            if (latinSquare[0][i] == tempMatrix[0]) {
                alpha = i;
                break;
            }
        }

        /*
        (6)
        Рассматриваем строку матрицы L,первый элемент которой
        совпадает с левым верхним элементом L''
        Обозначаем заданную этой строкой перестановку (номер строки) за beta
        */

        for (int i = 0; i < order; i++) {
            if (latinSquare[i][0] == tempMatrix[0]) {
                beta = i;
                break;
            }
        }

        /*
        (7)
        Проверяем что alpha и beta сохраняют операцию f'', то есть
        для любой пары 1 <= i, j <= order, выполнены равенства
        alpha(f''(qi,qj)) == f''(alpha(qi), alpha(qj))
        beta(f''(qi,qj)) == f''(beta(qi), beta(qj))
        Если неравенство хотя бы для одной пары, то неудача
        */

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (latinSquare[tempMatrix[j + i * order]][alpha] !=
                    tempMatrix[latinSquare[j][alpha] + latinSquare[i][alpha] * order] ||
                    latinSquare[beta][tempMatrix[j + i * order]] !=
                    tempMatrix[latinSquare[beta][j] + latinSquare[beta][i] * order])
                    return false;
            }
        }

        /*
        (8) - (9)
        Далее элемент в левом верхнем углу L обозначим за c.
        Проверяем что для любой пары 1 <= i, j <= order
        выполнено равенство:
        f(qi,qj) = f''(f''(alpha(qi), beta(qj)), c)
        Если хотя бы для одной пары неравенство, то неудача
        В противном случае - успех.
        */

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (latinSquare[i][j] !=
                    tempMatrix[latinSquare[0][0] +
                               tempMatrix[latinSquare[beta][j] + latinSquare[i][alpha] * order] * order])
                    return false;
            }
        }

        return true;
    }


    bool Quasigroup::IsSimple() {
        if (!setLatinSquare) {
            //std::cout << "[WARN]: call IsSimple(), but latin square is not set\n";
            if (setProperFamily)
                ProperFamiliesToLatinSquare();
            else {
                //std::cout << "[WARN]: Call IsSimple, but quasigroup is not set\n";
                return false;
            }
        }
        const int pairsCount = (order * (order - 1)) / 2;

        for (int j = 1; j < order; j++) {
            //UnorderedPair pairs[pairsCount];
            UnorderedPair *pairs = new UnorderedPair[pairsCount];
            std::queue<UnorderedPair> unrevEq;
            std::vector<int> classes[order];
            int classIndex[order];
            int equalPairsCount = 0;
            int maxClassSize = 2;
            bool classMost = false;

            int a = 0, b = 0;

            for (int t1 = 0; t1 < order; t1++) {
                for (int t2 = t1 + 1; t2 < order; t2++) {
                    pairs[CalculateIndex(t1, t2)] = {t1, t2};
                }
                classes[t1].push_back(t1);
                classIndex[t1] = t1;
            }

            MergeClasses(classes, classIndex, 0, j);
            equalPairsCount++;
            unrevEq.push(pairs[j - 1]);

            if (maxClassSize > order / 2)
                classMost = true;

            while (unrevEq.size() > 0 && !classMost) {
                a = unrevEq.front().firstElement;
                b = unrevEq.front().secondElement;
                unrevEq.pop();

                for (int i = 0; i < order; i++) {
                    int sa_line, sb_line, sa_column, sb_column;

                    sa_line = latinSquare[i][a];
                    sb_line = latinSquare[i][b];
                    sa_column = latinSquare[a][i];
                    sb_column = latinSquare[b][i];

                    if (classIndex[sa_line] != classIndex[sb_line]) {
                        unrevEq.push(pairs[CalculateIndex(sa_line, sb_line)]);
                        //!Сливаем классы
                        equalPairsCount +=
                                (int) classes[classIndex[sa_line]].size() * (int) classes[classIndex[sb_line]].size();
                        int newClassSize = MergeClasses(classes, classIndex, classIndex[sa_line], classIndex[sb_line]);
                        if (newClassSize > maxClassSize)
                            maxClassSize = newClassSize;
                    }

                    if (classIndex[sa_column] != classIndex[sb_column]) {
                        unrevEq.push(pairs[CalculateIndex(sa_column, sb_column)]);
                        //!Сливаем классы
                        equalPairsCount += (int) classes[classIndex[sa_column]].size() *
                                           (int) classes[classIndex[sb_column]].size();
                        int newClassSize = MergeClasses(classes, classIndex, classIndex[sa_column],
                                                        classIndex[sb_column]);
                        if (newClassSize > maxClassSize)
                            maxClassSize = newClassSize;
                    }

                    if (maxClassSize > order / 2) {
                        classMost = true;
                        break;
                    }
                }
            }

            delete[] pairs;

            if (equalPairsCount != pairsCount && !classMost)
                return false;
        }

        return true;
    }


    //! Возвращает размер полученного класса
    int Quasigroup::MergeClasses(std::vector<int> *classes, int *classIndex, int fclass, int sclass) {
        //! Всегда сливаем в первый класс
        if (fclass > sclass)
            std::swap(fclass, sclass);

        //! Все элементы из второго класса перекидываем в первый и изменяем номер класса переброшенного элемента
        //int startFClassSize = (int)classes[fclass].size();
        while (classes[sclass].size() > 0) {
            classes[fclass].push_back(classes[sclass][classes[sclass].size() - 1]);
            classIndex[classes[sclass][classes[sclass].size() - 1]] = fclass;
            classes[sclass].pop_back();
        }

        return (int) classes[fclass].size();
    }


    int Quasigroup::CalculateIndex(int t1, int t2) {
        if (t2 < t1)
            std::swap(t2, t1);

        return t1 * order + t2 - ((t1 + 1) * (t1 + 2)) / 2;
    }


    std::vector<int> Quasigroup::GetReversePermutation(std::vector<int> permutation) {
        std::vector<int> revPermutation(permutation.size());

        for (unsigned int i = 0; i < permutation.size(); i++)
            revPermutation[permutation[i]] = i;

        return revPermutation;
    }


    void Quasigroup::SwapLines(std::vector<int> *matrix, int i, int j) {
        for (int k = 0; k < order; k++)
            std::swap((*matrix)[k + i * order], (*matrix)[k + j * order]);
    }


    bool Quasigroup::IsSymmetricMatrix(std::vector<int> matrix) {
        for (int i = 0; i < order; i++) {
            for (int j = i + 1; j < order; j++) {
                if (matrix[j + i * order] != matrix[i + j * order])
                    return false;
            }
        }
        return true;
    }

    bool Quasigroup::TrueLatinSquare() {
        if (!setLatinSquare)
            return false;

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                for (int m = 0; m < order; m++) {
                    if (m != i && m != j &&
                        (latinSquare[i][m] == latinSquare[i][j] || latinSquare[m][j] == latinSquare[i][j]))
                        return false;
                }
            }
        }
        return true;
    }

    bool Quasigroup::TrueProperFamily() {
        if (!setProperFamily)
            return false;

        for (int i = 0; i < order; i++) {
            for (int j = i + 1; j < order; j++) {
                int s[n];
                int t[n];
                IntValueToKArray(i, s, n);
                IntValueToKArray(j, t, n);

                bool truePair = false;
                for (int m = 0; m < n; m++) {
                    if (s[m] != t[m] && properFamilies[m][i] == properFamilies[m][j])
                        truePair = true;
                }
                if (!truePair)
                    return false;
            }
        }
        return true;
    }

    bool Quasigroup::ContainsConstantFunction() {
        if (!setProperFamily) {
            std::cout << "[WARN]: Call ContainsConstantFunction, but proper families is not set \n";
            return false;
        }

        for (int i = 0; i < n; i++) {
            bool isConstantFunction = true;
            for (int j = 0; j < order - 1; j++) {
                if (properFamilies[i][j + 1] != properFamilies[i][j])
                    isConstantFunction = false;
            }
            if (isConstantFunction)
                return true;
        }
        return false;
    }

    void Quasigroup::PrintToFile(std::string filename, QuasigroupType format) {
        std::ofstream out(filename.c_str());
        if (format == LATIN_SQUARE) {
            out << order << " \n";

            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++)
                    out << latinSquare[i][j] << " ";
                out << "\n";
            }
        } else if (format == PROPER_FAMILY) {
            out << k << " \n" << n << " \n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < order; j++)
                    out << properFamilies[i][j] << " ";
                out << "\n";
            }
        }
        out.close();
    }

    std::ostream &operator<<(std::ostream &out, const Quasigroup &quasigroup) {
        if (quasigroup.setLatinSquare) {
            for (int i = 0; i < quasigroup.order; i++) {
                for (int j = 0; j < quasigroup.order; j++)
                    out << quasigroup.latinSquare[i][j] << " ";
                out << "\n";
            }
        } else if (quasigroup.setProperFamily) {
            for (int i = 0; i < quasigroup.n; i++) {
                for (int j = 0; j < quasigroup.order; j++)
                    out << quasigroup.properFamilies[i][j] << " ";
                out << "\n";
            }
        } else {
            out << "[ERROR]: Quasigroup is not set!\n";
        }
        return out;
    }

    bool operator==(const Quasigroup &q1, const Quasigroup &q2) {
        if (q1.order != q2.order)
            return false;

        if (q1.setLatinSquare && q2.setLatinSquare) {
            for (int i = 0; i < q1.order; i++) {
                for (int j = 0; j < q1.order; j++) {
                    if (q1.latinSquare[i][j] != q2.latinSquare[i][j])
                        return false;
                }
            }
            return true;
        } else if (q1.setProperFamily && q2.setProperFamily) {
            if (q1.n != q2.n || q1.k != q2.k)
                return false;

            for (int i = 0; i < q1.n; i++) {
                for (int j = 0; j < q1.order; j++) {
                    if (q1.properFamilies[i][j] != q2.properFamilies[i][j])
                        return false;
                }
            }
            return true;
        }

        return false;
    }
}