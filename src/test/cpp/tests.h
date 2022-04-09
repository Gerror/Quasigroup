//
// Created by Gerror on 18.02.2022.
//

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
     * с шагом step и числом шагов stepCount. Замеряет время работы и возвращает список вида order: time
     */
    std::map<int, double> checkLatinSquareQuasigroupGenerateTime(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int minOrder, int step, int stepCount);

    /*
     * Генерирует квазигруппы, задаваемые функционально, перебирая различные варианты k и n
     * с шагами kStep и nStep и числом шагов stepCount. Замеряет время работы и возвращает список вида order: time
     */
    std::map<int, double> checkFunctionalQuasigroupGenerateTime(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int startK, int startN, int kStep, int nStep, int stepCount);

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
     * Генерирует множество квазигрупп, задаваемых латинскими квадратами с порядком order в колличестве count штук.
     */
    std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateLatinSquareQuasigroupSet(LatinSquareQuasigroupFactory &latinSquareQuasigroupFactory, int order, int count);

    /*
     * Генерирует множество квазигрупп, задаваемых функционально с порядком k^n в колличестве count штук
     */
    std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> generateFunctionalQuasigroupSet(FunctionalQuasigroupFactory &functionalQuasigroupFactory, int k, int n, int count);

    /*
     * Посчитать число простых квазигрупп, заданных латинскими квадратами в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> simpleTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups);

    /*
     * Посчитать число аффинных квазигрупп, заданных латинскими квадратами в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> affineTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups);

    /*
     * Посчитать число простых квазигрупп, заданных функционально в множестве qusigroups
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> simpleTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups);

    /*
     * Посчитать число аффинных квазигрупп, заданных функционально в множестве qusigroups.
     * Возвращает колличество, худшее время, среднее время, лучшее время
     */
    tuple<int, double, double, double> affineTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups);
}

#endif //QUASIGROUP_TESTS_H
