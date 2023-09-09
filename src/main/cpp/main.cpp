#include "tests.h"
#include "JMQuasigroupFactory.h"
#include "SRQuasigroupFactory.h"
#include "FNQuasigroupFactory.h"
#include "PFQuasigroupFactory.h"
#include "AffineQuasigroupFactory.h"
#include "JMQuasigroup.h"
#include "PFQuasigroup.h"
#include "SRQuasigroup.h"
#include "FNQuasigroup.h"
#include "Quasigroup.h"
#include "AffineQuasigroup.h"

//using namespace Quasigroup;

int main() {

//    Quasigroup::JMQuasigroupFactory factory;
//    Quasigroup::PFQuasigroupFactory funcQuasigroupFactory;
//    Quasigroup::FNQuasigroupFactory funcQuasigroupFactory;

    int k = 2;
    int n = 2;
    int quasigroupCount = 100;
    Quasigroup::SRQuasigroupFactory factory;
//    Quasigroup::AffineQuasigroupFactory lsQuasigroupFactory;

    auto quasiSet = generateFunctionalQuasigroupSet(factory, k, n, quasigroupCount);
//    auto quasiSet = generateLatinSquareQuasigroupSet(factory, 4, 100);
    std::cout << "All quasigroups: " << quasiSet.size() << std::endl;


    //! LS tests
//    subquasigroupTestForLatinSquareQuasigroups(quasiSet, 2, true);
//    idempotentElementTestForLatinSquareQuasigroups(quasiSet, true);
//    affineTestForLatinSquareQuasigroups(quasiSet, false, true);

    //! Functional tests
//    subquasigroupTestForFunctionalQuasigroups(quasiSet, 2, true);
//    idempotentElementTestForFunctionalQuasigroups(quasiSet, true);
//    affineTestForFunctionalQuasigroups(quasiSet, true,true);
//    simpleTestForFunctionalQuasigroups(quasiSet, true);

    //! Generation time check
//    checkLatinSquareQuasigroupGenerateTime(lsQuasigroupFactory, 256, 0, 1, 1000, true);
//    checkFunctionalQuasigroupGenerateTime(funcQuasigroupFactory, 16, 2, 0, 0, 1, 1000, true);

    for (auto &q: quasiSet) {
        std::cout << *q << std::endl;

        delete q;
    }

    return 0;
}
