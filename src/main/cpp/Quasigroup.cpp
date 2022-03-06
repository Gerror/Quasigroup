//
// Created by rzhig on 04.03.2022.
//

#include "Quasigroup.h"

namespace Quasigroup {

    bool Quasigroup::isAffine() {
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

        for (int i = 1; i < order; i++)
            swapLines(&tempMatrix, i, tempMatrix[i * order], order);

        /*
         * (3)
         * Проверяем симметричность L'' (коммутативность f'')
         * Если не симметрична, то неудача
         */

        if (!isSymmetricMatrix(tempMatrix, order))
            return false;

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

    bool Quasigroup::isSimple() {
        const int pairsCount = (order * (order - 1)) / 2;

        for (int j = 1; j < order; j++) {
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

    std::ostream &operator<<(std::ostream &out, const Quasigroup &q) {
        for (int i = 0; i < q.order; i++) {
            for (int j = 0; j < q.order; j++)
                out << q.getProduct(i, j) << " ";
            out << std::endl;
        }
        return out;
    }

    bool operator==(const Quasigroup &q1, const Quasigroup &q2) {
        if (q1.order != q2.order) {
            return false;
        }

        int order = q1.order;

        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (q1.getProduct(i, j) != q2.getProduct(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

}