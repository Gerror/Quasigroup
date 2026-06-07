#ifndef QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H
#define QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H

#include "Experiment.h"

namespace Quasigroup {
class CheckPropertyTimeExperiment final : public Experiment {
  const std::function<void(Quasigroup *)> &checkPropertyFunction;

 public:
  explicit CheckPropertyTimeExperiment(
      const std::function<void(Quasigroup *)> &checkPropertyFunction);

  double iterate(std::vector<Quasigroup *> quasigroups) override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H