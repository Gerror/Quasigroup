//
// Created by Gerror on 04.03.2022.
//

#include "Quasigroup.h"

namespace Quasigroup {

    bool Quasigroup::isLoop() const {
        for (int i = 0; i < order; i++) {
            for (int j = i + 1; j < order; j++) {
                if (getProduct(j, i) != getProduct(i, j)) {
                    return false;
                }
            }

            if (getProduct(0, i) != i || getProduct(i, 0) != i) {
                return  false;
            }
        }
        return true;
    }

    bool Quasigroup::isAssociative() const {
        for (int r = 0; r < order; r++) {
            for (int s = 0; s < order; s++) {
                for (int t = 0; t < order; t++) {
                    if (getProduct(r, getProduct(s, t)) != getProduct(getProduct(r, s), t)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool Quasigroup::isAffine() const {
        /*
         * latinSquare далее - матрица L, её i-я строка - s(i)
         *
         * (1)
         * По матрице L строим матрицу L' (tempMatrix), в которой при каждом i = 1, ..., order
         * строка с номером i содержит перестановку s(i) * (s(1))^-1
         */

        std::vector<int> tempMatrix(order * order);
        std::vector<int> firstLine(order);
        std::vector<int> reverseFirstLine(order);
        int alpha, beta;

        for (int i = 0; i < order; i++)
            firstLine[i] = getProduct(0, i);

        reverseFirstLine = calculateReversePermutation(firstLine);

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++)
                tempMatrix[j + i * order] = getProduct(i, reverseFirstLine[j]);
        }

        /*
         * (2)
         * По матрице L' (tempMatrix) строим матрицу L'', полученную из L' перестановкой строк,
         * строк, такой что первый столбец L'' совпадает с первой строкой
         * Далее операция, порожденная матрицей L'' будем обозначать f''
         * (L'' хранится так же в tempMatrix)
         */

        for (int i = 1; i < order; i++) {
            while (i != tempMatrix[i * order]) {
                swapLines(&tempMatrix, i, tempMatrix[i * order], order);
            }
        }

        /*
         * (3)
         * Проверяем симметричность L'' (коммутативность f'')
         * Если не симметрична, то неудача
         */

        if (!isSymmetricMatrix(tempMatrix, order)) {
            return false;
        }

        /*
         * (4)
         * Проверяем ассоциативность f'', т.е. для всех r,s,t,
         * 1 <= r,s,t <= order
         * f''(f''(qr, qs), qt) == f''(qr, f''(qs, qt))
         * Если не ассоциативна, то неудача
         */

        for (int r = 0; r < order; r++) {
            for (int s = 0; s < order; s++) {
                for (int t = 0; t < order; t++) {
                    if (tempMatrix[t + tempMatrix[s + r * order] * order]
                            != tempMatrix[tempMatrix[t + s * order] + r * order]) {
                        return false;
                    }
                }
            }
        }

        /*
         * (5)
         * Рассматриваем столбец матрицы L,первый элемент которого
         * совпадает с левым верхним элементом L''
         * Обозначаем заданную этим столбцем перестановку (номер столбца) за alpha
         */

        for (int i = 0; i < order; i++) {
            if (getProduct(0, i) == tempMatrix[0]) {
                alpha = i;
                break;
            }
        }

        /*
         * (6)
         * Рассматриваем строку матрицы L,первый элемент которой
         * совпадает с левым верхним элементом L''
         * Обозначаем заданную этой строкой перестановку (номер строки) за beta
         */

        for (int i = 0; i < order; i++) {
            if (getProduct(i, 0) == tempMatrix[0]) {
                beta = i;
                break;
            }
        }

        /*
         * (7)
         * Проверяем что alpha и beta сохраняют операцию f'', то есть
         * для любой пары 1 <= i, j <= order, выполнены равенства
         * alpha(f''(qi,qj)) == f''(alpha(qi), alpha(qj))
         * beta(f''(qi,qj)) == f''(beta(qi), beta(qj))
         * Если неравенство хотя бы для одной пары, то неудача
         */

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (getProduct(tempMatrix[j + i * order], alpha)
                        != tempMatrix[getProduct(j, alpha) + getProduct(i, alpha) * order]
                        || getProduct(beta, tempMatrix[j + i * order])
                        != tempMatrix[getProduct(beta, j) + getProduct(beta, i) * order]) {

                    return false;
                }
            }
        }

        /*
         * (8) - (9)
         * Далее элемент в левом верхнем углу L обозначим за c.
         * Проверяем что для любой пары 1 <= i, j <= order
         * выполнено равенство:
         * f(qi,qj) = f''(f''(alpha(qi), beta(qj)), c)
         * Если хотя бы для одной пары неравенство, то неудача
         * В противном случае - успех.
         */

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (getProduct(i, j)
                        != tempMatrix[getProduct(0, 0)
                        + tempMatrix[getProduct(beta, j) + getProduct(i, alpha) * order] * order]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Quasigroup::isSimple() const {
        const int pairsCount = (order * (order - 1)) / 2;

        for (int j = 1; j < order; j++) {
            auto *pairs = new UnorderedPair[pairsCount];
            std::queue<UnorderedPair> unrevEq;
            std::vector<int> classes[order];
            int classIndex[order];
            int equalPairsCount = 0;
            int maxClassSize = 2;
            bool classMost = false;

            int a = 0, b = 0;

            for (int t1 = 0; t1 < order; t1++) {
                for (int t2 = t1 + 1; t2 < order; t2++) {
                    pairs[calculateUnorderedPairIndex(t1, t2, order)] = { t1, t2 };
                }
                classes[t1].push_back(t1);
                classIndex[t1] = t1;
            }

            mergeUnorderedPairClasses(classes, classIndex, 0, j);
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

                    sa_line = getProduct(i, a);
                    sb_line = getProduct(i, b);
                    sa_column = getProduct(a, i);
                    sb_column = getProduct(b, i);

                    if (classIndex[sa_line] != classIndex[sb_line]) {
                        unrevEq.push(pairs[calculateUnorderedPairIndex(sa_line, sb_line, order)]);

                        // Сливаем классы
                        equalPairsCount += (int) classes[classIndex[sa_line]].size() * (int) classes[classIndex[sb_line]].size();
                        int newClassSize = mergeUnorderedPairClasses(classes, classIndex, classIndex[sa_line], classIndex[sb_line]);
                        if (newClassSize > maxClassSize) {
                            maxClassSize = newClassSize;
                        }
                    }

                    if (classIndex[sa_column] != classIndex[sb_column]) {
                        unrevEq.push(pairs[calculateUnorderedPairIndex(sa_column, sb_column, order)]);

                        // Сливаем классы
                        equalPairsCount += (int) classes[classIndex[sa_column]].size() * (int) classes[classIndex[sb_column]].size();
                        int newClassSize = mergeUnorderedPairClasses(classes, classIndex, classIndex[sa_column], classIndex[sb_column]);
                        if (newClassSize > maxClassSize) {
                            maxClassSize = newClassSize;
                        }
                    }

                    if (maxClassSize > order / 2) {
                        classMost = true;
                        break;
                    }
                }
            }

            delete[] pairs;

            if (equalPairsCount != pairsCount && !classMost) {
                return false;
            }
        }

        return true;
    }

    int Quasigroup::getOrder() const {
        return order;
    }

    std::ostream &operator<<(std::ostream &out, const Quasigroup &q) {
        for (int i = 0; i < q.order; i++) {
            for (int j = 0; j < q.order; j++)
                out << q.getProduct(i, j) << " ";
            out << std::endl;
        }
        return out;
    }

    int Quasigroup::findSubquasigroup(int border, unsigned int **a_sq) const {
        unsigned int *seed, *a_sqi, *a_q;
        int i, last, retval;

        (*a_sq) = nullptr;
        a_sqi = nullptr;
        a_q = nullptr;
        retval = -1;

        seed = (unsigned int *) malloc (border * sizeof (unsigned int));
        if (seed == nullptr) {
            printf ("Failed to allocate memory\n");
            return -1;
        }

        do {
            (*a_sq) = (unsigned int *) malloc (sizeof (unsigned int) * order);
            if (a_sq == nullptr) {
                printf ("Failed to allocate memory\n");
                break;
            }
            a_sqi = (unsigned int *) malloc (sizeof (unsigned int) * order);
            if (a_sqi == nullptr) {
                printf ("Failed to allocate memory\n");
                break;
            }
            a_q = (unsigned int *) malloc (sizeof (unsigned int) * order);
            if (a_q == nullptr) {
                printf ("Failed to allocate memory\n");
                break;
            }

            for (i = 0; i < border; i++) {
                seed [i] = (unsigned int) i;
            }

            do {
                retval = checkStep(seed, border, *a_sq, a_sqi, a_q);
                if (retval != 0) {
                    break;
                }
                last = nextStep(seed, border);
                retval = checkStep(seed, border, *a_sq, a_sqi, a_q);
            } while (last == 0);
        } while (false);

        free (seed);
        if (((*a_sq) != nullptr) && (retval <= 0)) {
            free (*a_sq);
            (*a_sq) = nullptr;
        }
        if (a_sqi != nullptr) {
            free (a_sqi);
        }
        if (a_q != nullptr) {
            free (a_q);
        }

        return retval;
    }

    int Quasigroup::nextStep(unsigned int *step, int border) const {
        int i, cur;

        for (i = border - 1; i >= 0; i--) {
            if (step[i] < (order - 1) - (border - 1 - i)) {
                break;
            }
        }

        (step[i])++;
        cur = step[i] + 1;
        for (i = i + 1; i < border; i++) {
            step [i] = cur;
            cur++;
        }

        if (step [0] == order - border) {
            return 1;
        } else {
            return 0;
        }
    }

    int Quasigroup::checkStep(unsigned int *step, int border, unsigned int *a_sq,
                              unsigned int *a_sqi, unsigned int *a_q) const {
        int i, sqlen, retval, first, last;
        unsigned int cur, tmp;

        sqlen = border;
        first = 0;
        last = border;
        retval = 0;

        // initialization
        memset (a_sq, 0, sizeof (unsigned int) * order);
        memset (a_sqi, 0, sizeof (unsigned int) * order);
        memset (a_q, 0, sizeof (unsigned int) * order);
        for (i = 0; i < border; i++) {
            a_sq [i] = step [i];
            a_sqi [step [i]] = 3;
            a_q [i] = step [i];
        }

        // build the closure of the seed
        while (last - first > 0) {
            cur = a_q [first];
            first++;

            tmp = getProduct(cur, cur);
            if (a_sqi [tmp] == 0) {
                a_q [last] = tmp;
                a_sqi [tmp] = 2;
                last++;
            }

            for (i = 0; i < sqlen; i++) {
                tmp = getProduct(a_sq[i], cur);
                if (a_sqi [tmp] == 0) {
                    a_q [last] = tmp;
                    a_sqi [tmp] = 2;
                    last++;
                }
                tmp = getProduct(cur, a_sq [i]);
                if (a_sqi [tmp] == 0) {
                    a_q [last] = tmp;
                    a_sqi [tmp] = 2;
                    last++;
                }
            }

            if ((a_sqi [cur] % 2) == 0) {
                a_sq [sqlen] = cur;
                a_sqi [cur] = 1;
                sqlen++;
            }
        }
        if (last - first + sqlen <= order / 2) {
            // a subquasigroup is found
            retval = sqlen;
        }

        return retval;
    }

    std::unordered_set<int> Quasigroup::getGenerationSystem() {
        std::unordered_set<int> *generationSystem = new std::unordered_set<int>();
        std::unordered_set<int> *tempQ = new std::unordered_set<int>();
        std::unordered_set<int> *newQ = new std::unordered_set<int>();

        generationSystem->insert(0);
        newQ->insert(0);
        for (int i = 1; i < order; i++) {
            tempQ->insert(i);
        }

        int currentSize = newQ->size();
        int currentElement = 0;
        do {
            currentSize = newQ->size();
            currentElement = getProduct(0, currentElement);
            newQ->insert(currentElement);
            if (newQ->size() != currentSize) {
                tempQ->erase(currentElement);
            }
        } while(newQ->size() != currentSize);

        while (!tempQ->empty()) {
            int begin = (*tempQ->begin());
            generationSystem->insert(begin);
            for (const auto& elem: *newQ) {
                newQ->insert(getProduct(elem, begin));
                newQ->insert(getProduct(begin, elem));

                if (tempQ->count(getProduct(elem, begin)) > 0) {
                    tempQ->erase(getProduct(elem, begin));
                }

                if (tempQ->count(getProduct(begin, elem)) > 0) {
                    tempQ->erase(getProduct(begin, elem));
                }
            }

            newQ->insert(begin);
            tempQ->erase(begin);

            int currentSize;
            int currentElement = begin;
            do {
                currentSize = newQ->size();
                currentElement = getProduct(begin, currentElement);
                newQ->insert(currentElement);
                if (newQ->size() != currentSize) {
                    tempQ->erase(currentElement);
                }
            } while(newQ->size() != currentSize);
        }

        return *generationSystem;
    }

    size_t Quasigroup::QuasigroupHash::operator()(const Quasigroup *quasigroup) const {
        std::hash<std::string> hasher;
        std::string hash = "";
        for (int y = 0; y < quasigroup->getOrder(); y++) {
            for (int x = 0; x < quasigroup->getOrder(); x++) {
                hash += std::to_string(quasigroup->getProduct(x, y)) + " ";
            }
            hash += "\n";
        }
        return hasher(hash);
    }

    bool Quasigroup::QuasigroupEqualHash::operator()(const Quasigroup *q1, const Quasigroup *q2) const {
        Quasigroup::QuasigroupHash hasher;
        return hasher(q1) == hasher(q2);
    }

}