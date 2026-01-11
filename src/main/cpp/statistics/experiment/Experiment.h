#ifndef QUASIGROUP_EXPERIMENT_H
#define QUASIGROUP_EXPERIMENT_H

#include <generator/QuasigroupGenerator.h>

namespace Quasigroup {
class Experiment {
 public:
  virtual double iterate(QuasigroupGenerator *generator, int objectsCount) = 0;

  virtual ~Experiment() = default;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_EXPERIMENT_H