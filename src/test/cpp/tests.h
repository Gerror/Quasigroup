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

#include "Quasigroup.h"
#include "IncidenceCube.h"
#include "ProperFamily.h"
#include "Helper.h"

using namespace std;

namespace Quasigroup {

    bool checkCorrectnessLatinSquare(Quasigroup &q);
    bool checkCorrectnessProperFamily(ProperFamily &pf);

}

#endif //QUASIGROUP_TESTS_H
