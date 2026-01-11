#ifndef QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H
#define QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H

#include "Experiment.h"

namespace Quasigroup {
class CheckPropertyTimeExperiment : public Experiment {
  const std::function<void(Quasigroup *)> &checkPropertyFunction;

 public:
  explicit CheckPropertyTimeExperiment(
      const std::function<void(Quasigroup *)> &checkPropertyFunction);

  double iterate(QuasigroupGenerator *generator, int objectsCount) override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H