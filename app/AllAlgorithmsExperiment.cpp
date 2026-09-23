#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>

#include "CheckPropertyTimeExperiment.h"
#include "ExperimentsRunner.h"
#include "JMQuasigroupFactory.h"
#include "Quasigroup.h"
#include "QuasigroupExperiments.h"
#include "QuasigroupGenerator.h"

namespace QuasigroupExperiments {

void runAllAlgorithmsExperimentOnJMQuasigroups(int qSizeStart, int qSizeEnd,
                                               int countPerIterations) {
  std::ofstream outfileLight("affinity_jm_light.txt");
  std::ofstream outfileCompleteSearch("affinity_jm_complete_search.txt");
  std::ofstream outfileBasisAssociativity("affinity_jm_basis.txt");
  std::ofstream outfileSimple("simple_jm.txt");
  std::ofstream outfileShapeless("shapeless_jm.txt");
  std::ofstream outfileSubquasigroup("subquasigroup_jm.txt");

  for (int i = qSizeStart; i <= qSizeEnd; i++) {
    std::cout << "Start iteration " << i << std::endl;
    Quasigroup::JMQuasigroupFactory factory(i);
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

    Quasigroup::CheckPropertyTimeExperiment experimentSimple(
        [](const Quasigroup::Quasigroup *q) { return q->isSimple(); });

    Quasigroup::CheckPropertyTimeExperiment experimentShapeless(
        [](Quasigroup::Quasigroup *q) { return q->isShapeless(); });

    Quasigroup::CheckPropertyTimeExperiment experimentSubquasigroup(
        [](const Quasigroup::Quasigroup *q) {
          return q->containsAnyProperSubquasigroup();
        });

    const auto reportLight = runner.run(quasigroups, &experimentLight);
    const auto reportCompleteSearch =
        runner.run(quasigroups, &experimentCompleteSearch);
    const auto reportBasis4Associativity =
        runner.run(quasigroups, &experiment4Associativity);
    const auto reportSimple = runner.run(quasigroups, &experimentSimple);
    const auto reportShapeless = runner.run(quasigroups, &experimentShapeless);
    const auto reportSubquasigroup =
        runner.run(quasigroups, &experimentSubquasigroup);

    outfileLight << std::fixed << std::setprecision(6) << i << " "
                 << reportLight->getAverageFraction() << std::endl;

    outfileCompleteSearch << std::fixed << std::setprecision(6) << i << " "
                          << reportCompleteSearch->getAverageFraction()
                          << std::endl;

    outfileBasisAssociativity << std::fixed << std::setprecision(6) << i << " "
                              << reportBasis4Associativity->getAverageFraction()
                              << std::endl;

    outfileSimple << std::fixed << std::setprecision(6) << i << " "
                  << reportSimple->getAverageFraction() << std::endl;

    outfileShapeless << std::fixed << std::setprecision(6) << i << " "
                     << reportShapeless->getAverageFraction() << std::endl;

    outfileSubquasigroup << std::fixed << std::setprecision(6) << i << " "
                         << reportSubquasigroup->getAverageFraction()
                         << std::endl;

    delete reportLight;
    delete reportCompleteSearch;
    delete reportBasis4Associativity;
    delete reportSimple;
    delete reportShapeless;
    delete reportSubquasigroup;
    for (auto q : quasigroups) {
      delete q;
    }
    quasigroups.clear();
  }

  outfileLight.close();
  outfileCompleteSearch.close();
  outfileBasisAssociativity.close();
  outfileSimple.close();
  outfileShapeless.close();
  outfileSubquasigroup.close();
}

}  // namespace QuasigroupExperiments