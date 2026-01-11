#ifndef QUASIGROUP_GENERATIONTIMEEXPERIMENT_H
#define QUASIGROUP_GENERATIONTIMEEXPERIMENT_H

#include "Experiment.h"

namespace Quasigroup {
class GenerationTimeExperiment final : public Experiment {
 public:
  double iterate(QuasigroupGenerator *generator, int objectsCount) override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_GENERATIONTIMEEXPERIMENT_H