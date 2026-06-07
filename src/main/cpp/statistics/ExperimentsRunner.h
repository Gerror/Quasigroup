#ifndef QUASIGROUP_EXPERIMENTSRUNNER_H
#define QUASIGROUP_EXPERIMENTSRUNNER_H

#include <quasigroup/factory/QuasigroupFactory.h>

#include "Experiment.h"
#include "ExperimentalReport.h"

namespace Quasigroup {
class ExperimentsRunner {
 public:
  ExperimentalReport *run(QuasigroupFactory *factory, int iterations,
                          int objectsPerIteration,
                          Experiment *experiment) const;

  ExperimentalReport *run(const std::vector<Quasigroup *> &quasigroups,
                          Experiment *experiment) const;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_EXPERIMENTSRUNNER_H