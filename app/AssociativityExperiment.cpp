#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>

#include "AbelianGroupFactory.h"
#include "CheckPropertyTimeExperiment.h"
#include "ExperimentsRunner.h"
#include "Quasigroup.h"
#include "QuasigroupExperiments.h"
#include "QuasigroupGenerator.h"

namespace QuasigroupExperiments {

void runAssociativityExperimentOnAbelianGroups(int qSizeStart, int qSizeEnd,
                                               int countPerIterations) {
  std::ofstream outfileLight("associativity_ag_light.txt");
  std::ofstream outfileCompleteSearch("associativity_ag_complete_search.txt");
  std::ofstream outfile4Associativity("associativity_ag_basis.txt");

  for (int i = qSizeStart; i <= qSizeEnd; i++) {
    std::cout << "Start iteration " << i << std::endl;
    Quasigroup::AbelianGroupFactory factory(i);
    Quasigroup::QuasigroupGenerator generator(&factory);
    auto quasigroups = generator.generateVector(countPerIterations);
    std::cout << "Quasigroups generated on iteration " << i << std::endl;
    Quasigroup::ExperimentsRunner runner;

    Quasigroup::CheckPropertyTimeExperiment experimentLight(
        [](const Quasigroup::Quasigroup *q) {
          return q->isAffine(
              Quasigroup::AssociativityDeterminationStrategy::LightTest);
        });

    Quasigroup::CheckPropertyTimeExperiment experimentCompleteSearch(
        [](const Quasigroup::Quasigroup *q) {
          return q->isAffine(
              Quasigroup::AssociativityDeterminationStrategy::CompleteSearch);
        });

    Quasigroup::CheckPropertyTimeExperiment experiment4Associativity(
        [](const Quasigroup::Quasigroup *q) {
          return q->isAffine(Quasigroup::AssociativityDeterminationStrategy::
                                 BasisAssociativity);
        });

    const auto reportLight = runner.run(quasigroups, &experimentLight);
    const auto reportCompleteSearch =
        runner.run(quasigroups, &experimentCompleteSearch);
    const auto reportBasis4Associativity =
        runner.run(quasigroups, &experiment4Associativity);

    outfileLight << std::fixed << std::setprecision(6) << i << " "
                 << reportLight->getAverageFraction() << std::endl;

    outfileCompleteSearch << std::fixed << std::setprecision(6) << i << " "
                          << reportCompleteSearch->getAverageFraction()
                          << std::endl;

    outfile4Associativity << std::fixed << std::setprecision(6) << i << " "
                          << reportBasis4Associativity->getAverageFraction()
                          << std::endl;

    delete reportLight;
    delete reportCompleteSearch;
    delete reportBasis4Associativity;
    for (auto q : quasigroups) {
      delete q;
    }
    quasigroups.clear();
  }

  outfileLight.close();
  outfileCompleteSearch.close();
  outfile4Associativity.close();
}

}  // namespace QuasigroupExperiments