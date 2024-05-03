#ifndef QUASIGROUP_TESTS_H
#define QUASIGROUP_TESTS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <map>
#include <unordered_set>

#include "Quasigroup.h"
#include "IncidenceCube.h"
#include "ProperFamily.h"
#include "Helper.h"
#include "LatinSquareQuasigroupFactory.h"
#include "FunctionalQuasigroupFactory.h"

using namespace std;

namespace Quasigroup {

    bool checkCorrectnessLatinSquare(Quasigroup &q);

    bool checkCorrectnessProperFamily(ProperFamily &pf);

    /*
     * Генерирует квазигруппы, представленные в виде латинских квадратов, начиная от порядка minOrder
     * с шагом step и числом шагов stepCount в количестве count штук.
     * Замеряет время работы и возвращает map вида order: <count, worst time, average time, best time>
     */
    std::map<int, tuple<int, double, double, double>> checkLatinSquareQuasigroupGenerateTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount, int count, bool printResult = false);

    /*
     * Генерирует квазигруппы, задаваемые функционально, перебирая различные варианты k и n
     * с шагами kStep и nStep и числом шагов stepCount в количестве count штук.
     * Замеряет время работы и возвращает map вида order: <count, worst time, average time, best time>
     */
    std::map<int, tuple<int, double, double, double>> checkFunctionalQuasigroupGenerateTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount, int count, bool printResult = false);

    /*
     * Генерация и проверка на простоту квазигрупп, задаваемых латинскими квадратами
     */
    std::map<int, double> checkLatinSquareQuasigroupIsSimpleTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount);

    /*
     * Генерация и проверка на простоту квазигрупп, задаваемых функционально
     */
    std::map<int, double> checkFunctionalQuasigroupIsSimpleTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount);

    /*
     * Генерация и проверка на аффинность квазигрупп, задаваемых латинскими квадратами
     */
    std::map<int, double> checkLatinSquareQuasigroupIsAffineTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount);

    /*
     * Генерация и проверка на аффинность квазигрупп, задаваемых функционально
     */
    std::map<int, double> checkFunctionalQuasigroupIsAffineTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount);

    /*
     * Генерирует множество квазигрупп, задаваемых латинскими квадратами с порядком order в колличестве count штук, удаляя повторы
     */
    std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateLatinSquareQuasigroupSet(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int order, int count);

    /*
     * Генерирует множество квазигрупп, задаваемых функционально с порядком k^n в колличестве count штук, удаляя повторы
     */
    std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateFunctionalQuasigroupSet(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int k, int n, int count);

    /*
     * Генерирует множество уникальных квазигрупп, задаваемых латинскими квадратами с порядком order размера count.
     * WARNING: Может продолжаться бесконечно долго, если квазигрупп существует меньше, чем count
     */
    std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateLatinSquareQuasigroupUniqueSet(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int order, int count);

    /*
     * Генерирует множество уникальных квазигрупп, задаваемых функционально с порядком k^n размера count.
     * WARNING: Может продолжаться бесконечно долго, если квазигрупп существует меньше, чем count
     */
    std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateFunctionalQuasigroupUniqueSet(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int k, int n, int count);


    /*
     * Посчитать число простых квазигрупп, заданных латинскими квадратами в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> simpleTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

    /*
     * Посчитать число аффинных квазигрупп, заданных латинскими квадратами в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> affineTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest = false, bool printResult = false);

    /*
     * Посчитать число простых квазигрупп, заданных функционально в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> simpleTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

    /*
     * Посчитать число аффинных квазигрупп, заданных функционально в множестве qusigroups.
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> affineTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest = false, bool printResult = false);

    /*
     * Считает колличество функциональных квазигрупп у которых есть подквазигруппы порядка не менее чем border
     */
    int subquasigroupTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult = false);

    /*
    * Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка не менее чем border
    */
    int subquasigroupTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult = false);

    /*
    * Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка 1
    */
    int idempotentElementTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

    /*
    * Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка 1
    */
    int idempotentElementTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);
}

#endif //QUASIGROUP_TESTS_H
