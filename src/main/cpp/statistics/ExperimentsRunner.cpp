#include "ExperimentsRunner.h"

namespace Quasigroup {
ExperimentalReport *ExperimentsRunner::run(QuasigroupFactory *factory,
                                           const int iterations,
                                           const int objectsPerIteration,
                                           Experiment *experiment) const {
  const QuasigroupGenerator generator(factory);
  std::vector<double> results(iterations);
  for (int i = 0; i < iterations; i++) {
    results[i] = experiment->iterate(&generator, objectsPerIteration);
  }
  const auto report = new ExperimentalReport(factory->getOrder(), iterations,
                                             objectsPerIteration, results);
  return report;
}

ExperimentalReport *ExperimentsRunner::run(
    const std::vector<Quasigroup *> &quasigroups,
    Experiment *experiment) const {
  const std::vector results = {experiment->iterate(quasigroups)};
  return new ExperimentalReport(quasigroups[0]->getOrder(), 1,
                                quasigroups.size(), results);
}

}  // namespace Quasigroup