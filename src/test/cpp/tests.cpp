//
// Created by Gerror on 18.02.2022.
//

#include "tests.h"

namespace Quasigroup {

    bool checkCorrectnessLatinSquare(Quasigroup &q) {
        for (int i = 0; i < q.getOrder(); i++) {
            for (int j = 0; j < q.getOrder(); j++) {
                for (int m = 0; m < q.getOrder(); m++) {
                    if (m != i && m != j && (q.getProduct(i, m) == q.getProduct(i, j) || q.getProduct(m, j) == q.getProduct(i, j))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool checkCorrectnessProperFamily(ProperFamily &pf) {
        for (int i = 0; i < pf.getOrder(); i++)
        {
            for (int j = i + 1; j < pf.getOrder(); j++)
            {
                int s[pf.getN()];
                int t[pf.getN()];
                intValueToKArray(i, pf.getK(), s, pf.getN());
                intValueToKArray(j, pf.getK(), t, pf.getN());

                bool truePair = false;
                for (int m = 0; m < pf.getN(); m++)
                {
                    if (s[m] != t[m] && pf.getFunctionValue(i, m) == pf.getFunctionValue(j, m)) {
                        truePair = true;
                    }
                }
                if (!truePair) {
                    return false;
                }
            }
        }
        return true;
    }

    std::map<int, tuple<int, double, double, double>> checkLatinSquareQuasigroupGenerateTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount, int count, bool printResult) {
        std::map<int, tuple<int, double, double, double>> result;

        for (int i = 0; i < stepCount; i++) {
            int order = minOrder + i * step;
            tuple<int, double, double, double> values = {0, 0.0, 0.0, -1.0};

            for (int j = 0; j < count; j++) {
                auto begin = chrono::steady_clock::now();

                LatinSquareQuasigroup *latinSquareQuasigroup = latinSquareQuasigroupFactory.createQuasigroup(order);

                auto end = chrono::steady_clock::now();

                auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                double time = elapsed.count() / 1000000.0;

                values = increaseResult(values, time, true, count);

                delete latinSquareQuasigroup;
            }

            result.insert(std::make_pair(order, values));
        }

        if (printResult) {
            for (auto &item: result) {
                std::cout << "order " << item.first << std::endl <<
                          "count " << get<0>(item.second) << std::endl <<
                          "worst time " << get<1>(item.second) << std::endl <<
                          "average time " << get<2>(item.second) << std::endl <<
                          "best time " << get<3>(item.second) << std::endl << std::endl;
            }
        }

        return result;
    }

    std::map<int, tuple<int, double, double, double>> checkFunctionalQuasigroupGenerateTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount, int count, bool printResult) {
        std::map<int, tuple<int, double, double, double>> result;

        for (int i = 0; i < stepCount; i++) {
            int k = startK + i * kStep;
            int n = startN + i * nStep;
            int order;
            tuple<int, double, double, double> values = {0, 0.0, 0.0, -1.0};

            for (int j = 0; j < count; j++) {
                std::cout << j << std::endl;

                auto begin = chrono::steady_clock::now();

                FunctionalQuasigroup *functionalQuasigroup = functionalQuasigroupFactory.createQuasigroup(k, n);
                LatinSquareQuasigroup latinSquareQuasigroup(*functionalQuasigroup);

                auto end = chrono::steady_clock::now();

                auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
                double time = elapsed.count() / 1000000.0;

                values = increaseResult(values, time, true, count);

                order = functionalQuasigroup->getOrder();

                delete functionalQuasigroup;
            }

            result.insert(std::make_pair(order, values));
        }

        if (printResult) {
            for (auto &item: result) {
                std::cout << "order " << item.first << std::endl <<
                             "count " << get<0>(item.second) << std::endl <<
                             "worst time " << get<1>(item.second) << std::endl <<
                             "average time " << get<2>(item.second) << std::endl <<
                             "best time " << get<3>(item.second) << std::endl << std::endl;
            }
        }

        return result;
    }

    std::map<int, double> checkLatinSquareQuasigroupIsSimpleTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount) {
        std::map<int, double> result;
        for (int i = 0; i < stepCount; i++) {
            int order = minOrder + i * step;
            LatinSquareQuasigroup *latinSquareQuasigroup = latinSquareQuasigroupFactory.createQuasigroup(order);
            auto begin = chrono::steady_clock::now();
            bool isSimple = latinSquareQuasigroup->isSimple();
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result.insert(std::make_pair(order, time));
            delete latinSquareQuasigroup;
        }
        return result;
    }

    std::map<int, double> checkFunctionalQuasigroupIsSimpleTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount) {
        std::map<int, double> result;
        for (int i = 0; i < stepCount; i++) {
            int k = startK + i * kStep;
            int n = startN + i * nStep;
            FunctionalQuasigroup *functionalQuasigroup = functionalQuasigroupFactory.createQuasigroup(k, n);
            LatinSquareQuasigroup latinSquareQuasigroup(*functionalQuasigroup);
            auto begin = chrono::steady_clock::now();
            bool isSimple = latinSquareQuasigroup.isSimple();
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result.insert(std::make_pair(functionalQuasigroup->getOrder(), time));
            delete functionalQuasigroup;
        }
        return result;
    }

    std::map<int, double> checkLatinSquareQuasigroupIsAffineTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount) {
        std::map<int, double> result;
        for (int i = 0; i < stepCount; i++) {
            int order = minOrder + i * step;
            LatinSquareQuasigroup *latinSquareQuasigroup = latinSquareQuasigroupFactory.createQuasigroup(order);
            auto begin = chrono::steady_clock::now();
            bool isAffine = latinSquareQuasigroup->isAffine();
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result.insert(std::make_pair(order, time));
            delete latinSquareQuasigroup;
        }
        return result;
    }

    std::map<int, double> checkFunctionalQuasigroupIsAffineTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount) {
        std::map<int, double> result;
        for (int i = 0; i < stepCount; i++) {
            int k = startK + i * kStep;
            int n = startN + i * nStep;
            FunctionalQuasigroup *functionalQuasigroup = functionalQuasigroupFactory.createQuasigroup(k, n);
            LatinSquareQuasigroup latinSquareQuasigroup(*functionalQuasigroup);
            auto begin = chrono::steady_clock::now();
            bool isAffine = latinSquareQuasigroup.isAffine();
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result.insert(std::make_pair(functionalQuasigroup->getOrder(), time));
            delete functionalQuasigroup;
        }
        return result;
    }


    std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateLatinSquareQuasigroupSet(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int order, int count) {
        std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> result;
        int sizeBefore, sizeAfter;
        for (int i = 0; i < count; i++) {
            LatinSquareQuasigroup *latinSquareQuasigroup = latinSquareQuasigroupFactory.createQuasigroup(order);
            sizeBefore = result.size();
            result.insert(latinSquareQuasigroup);
            sizeAfter = result.size();
            if (sizeAfter == sizeBefore) {
                delete latinSquareQuasigroup;
            }
        }
        return result;
    }

    std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateFunctionalQuasigroupSet(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int k, int n, int count) {
        std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> result;
        int sizeBefore, sizeAfter;
        for (int i = 0; i < count; i++) {
            FunctionalQuasigroup *functionalQuasigroup = functionalQuasigroupFactory.createQuasigroup(k, n);
            sizeBefore = result.size();
            result.insert(functionalQuasigroup);
            sizeAfter = result.size();
            if (sizeAfter == sizeBefore) {
                delete functionalQuasigroup;
            }
        }
        return result;
    }

    tuple<int, double, double, double> simpleTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult) {
        tuple<int, double, double, double> result = {0, 0.0, 0.0, -1.0};
        for (auto const &item: quasigroups) {
            auto begin = chrono::steady_clock::now();

            bool isSimple = item->isSimple();

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result = increaseResult(result, time, isSimple, quasigroups.size());
        }

        if (printResult) {
            std::cout <<
                      "Simple count " << get<0>(result) << std::endl <<
                      "Simple worst time " << get<1>(result) << std::endl <<
                      "Simple average time " << get<2>(result) << std::endl <<
                      "Simple best time " << get<3>(result) << std::endl << std::endl;
        }

        return result;
    }

    tuple<int, double, double, double> affineTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest, bool printResult) {
        tuple<int, double, double, double> result = {0, 0.0, 0.0, -1.0};
        for (auto const &item: quasigroups) {
            auto begin = chrono::steady_clock::now();

            bool isAffine = item->isAffine(useLightTest);

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result = increaseResult(result, time, isAffine, quasigroups.size());
        }

        if (printResult) {
            std::cout <<
                      "Affine count " << get<0>(result) << std::endl <<
                      "Affine worst time " << get<1>(result) << std::endl <<
                      "Affine average time " << get<2>(result) << std::endl <<
                      "Affine best time " << get<3>(result) << std::endl << std::endl;
        }

        return result;
    }

    tuple<int, double, double, double> simpleTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult) {
        tuple<int, double, double, double> result = {0, 0.0, 0.0, -1.0};
        for (auto const &item: quasigroups) {
            LatinSquareQuasigroup latinSquareQuasigroup(*item);

            auto begin = chrono::steady_clock::now();

            bool isSimple = latinSquareQuasigroup.isSimple();

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result = increaseResult(result, time, isSimple, quasigroups.size());
        }

        if (printResult) {
            std::cout <<
              "Simple count " << get<0>(result) << std::endl <<
              "Simple worst time " << get<1>(result) << std::endl <<
              "Simple average time " << get<2>(result) << std::endl <<
              "Simple best time " << get<3>(result) << std::endl << std::endl;
        }

        return result;
    }

    tuple<int, double, double, double> affineTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest, bool printResult) {
        tuple<int, double, double, double> result = {0, 0.0, 0.0, -1.0};
        for (auto const &item: quasigroups) {
            LatinSquareQuasigroup latinSquareQuasigroup(*item);

            auto begin = chrono::steady_clock::now();

            bool isAffine = latinSquareQuasigroup.isAffine(useLightTest);

            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count()/1000000.0;

            result = increaseResult(result, time, isAffine, quasigroups.size());
        }

        if (printResult) {
            std::cout <<
                      "Affine count " << get<0>(result) << std::endl <<
                      "Affine worst time " << get<1>(result) << std::endl <<
                      "Affine average time " << get<2>(result) << std::endl <<
                      "Affine best time " << get<3>(result) << std::endl << std::endl;
        }

        return result;
    }

    int subquasigroupTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult) {
        int result = 0;

        for (auto const &item: quasigroups) {
            unsigned int *sqg;
            sqg = nullptr;

            int findSubgroupResult = item->findSubquasigroup(border, &sqg);
            if (findSubgroupResult > 0) {
                result++;
            }

            if (sqg != nullptr) {
                free (sqg);
            }
        }

        if (printResult) {
            std::cout << "Non trivial subgroups: " << result << std::endl;
        }

        return result;
    }

    int subquasigroupTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult) {
        int result = 0;
        for (auto const &item: quasigroups) {
            unsigned int *sqg;
            sqg = nullptr;

            int findSubgroupResult = item->findSubquasigroup(border, &sqg);
            if (findSubgroupResult > 0) {
                result++;
            }

            if (sqg != nullptr) {
                free (sqg);
            }
        }

        if (printResult) {
            std::cout << "Non trivial subgroups: " << result << std::endl;
        }

        return result;
    }

    int idempotentElementTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult) {
        int result = 0;

        for (auto const &item: quasigroups) {
            for (int i = 0; i < item->getOrder(); i++) {
                if (item->getProduct(i, i) == i) {
                    result++;
                    break;
                }
            }
        }

        if (printResult) {
            std::cout << "Trivial subgroups: " << result << std::endl;
        }

        return result;
    }

    int idempotentElementTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult) {
        int result = 0;

        for (auto const &item: quasigroups) {
            for (int i = 0; i < item->getOrder(); i++) {
                if (item->getProduct(i, i) == i) {
                    result++;
                    break;
                }
            }
        }

        if (printResult) {
            std::cout << "Trivial subgroups: " << result << std::endl;
        }

        return result;
    }

}