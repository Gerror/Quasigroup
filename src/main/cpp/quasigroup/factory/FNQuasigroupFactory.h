#ifndef QUASIGROUP_FNQUASIGROUPFACTORY_H
#define QUASIGROUP_FNQUASIGROUPFACTORY_H

#include "FNQuasigroup.h"
#include "FunctionalQuasigroupFactory.h"

namespace Quasigroup {
class FNQuasigroupFactory final : public FunctionalQuasigroupFactory {
  bool inverseOperations;

 public:
  explicit FNQuasigroupFactory(const int k,
                               const bool inverseOperations = false)
      : FunctionalQuasigroupFactory(k, 2),
        inverseOperations(inverseOperations) {};

  FNQuasigroup *create() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_FNQUASIGROUPFACTORY_H