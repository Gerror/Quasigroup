#ifndef QUASIGROUP_SRQUASIGROUPFACTORY_H
#define QUASIGROUP_SRQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "SRQuasigroup.h"

namespace Quasigroup {
class SRQuasigroupFactory final : public FunctionalQuasigroupFactory {
  bool inverseOperations;

 public:
  explicit SRQuasigroupFactory(const int k, const int n,
                               const bool inverseOperations = false)
      : FunctionalQuasigroupFactory(k, n),
        inverseOperations(inverseOperations) {};

  SRQuasigroup *create() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_SRQUASIGROUPFACTORY_H