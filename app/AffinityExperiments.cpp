#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>

#include "AffineQuasigroupFactory.h"
#include "CheckPropertyTimeExperiment.h"
#include "ExperimentsRunner.h"
#include "Quasigroup.h"
#include "QuasigroupGenerator.h"

namespace QuasigroupExperiments {

void runAffinityExperimentOnAbelianGroups(int qSizeStart, int qSizeEnd,
                                          int countPerIterations) {
  std::ofstream outfileLight("affinity_ag_light.txt");
  std::ofstream outfileCompleteSearch("affinity_ag_complete_search.txt");
  std::ofstream outfile4Associativity("affinity_ag_basis.txt");

  for (int i = qSizeStart; i <= qSizeEnd; i++) {
    std::cout << "Start iteration " << i << std::endl;
    Quasigroup::AffineQuasigroupFactory factory(i);
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