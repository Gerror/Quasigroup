#ifndef QUASIGROUP_EXPERIMENT_H
#define QUASIGROUP_EXPERIMENT_H

#include <generator/QuasigroupGenerator.h>

namespace Quasigroup {
class Experiment {
 public:
  virtual ~Experiment() = default;
  virtual double iterate(const QuasigroupGenerator *generator,
                         const int objectsCount) {
    return iterate(generator->generateVector(objectsCount));
  }
  virtual double iterate(std::vector<Quasigroup *> quasigroups) = 0;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_EXPERIMENT_H