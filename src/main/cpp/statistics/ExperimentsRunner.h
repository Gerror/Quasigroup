#ifndef QUASIGROUP_EXPERIMENTSRUNNER_H
#define QUASIGROUP_EXPERIMENTSRUNNER_H

#include <generator/QuasigroupGenerator.h>
#include <quasigroup/factory/QuasigroupFactory.h>

#include "Experiment.h"
#include "ExperimentalReport.h"

namespace Quasigroup {
class ExperimentsRunner {
  QuasigroupFactory *factory;
  QuasigroupGenerator *generator;

 public:
  explicit ExperimentsRunner(QuasigroupFactory *factory);

  ~ExperimentsRunner();

  ExperimentalReport *run(int iterations, int objectsPerIteration,
                          Experiment *experiment) const;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_EXPERIMENTSRUNNER_H