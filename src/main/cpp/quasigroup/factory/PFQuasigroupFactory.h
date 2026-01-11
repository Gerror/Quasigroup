#ifndef QUASIGROUP_PFQUASIGROUPFACTORY_H
#define QUASIGROUP_PFQUASIGROUPFACTORY_H

#include "FunctionalQuasigroupFactory.h"
#include "PFQuasigroup.h"

namespace Quasigroup {
class PFQuasigroupFactory final : public FunctionalQuasigroupFactory {
 public:
  PFQuasigroupFactory(const int k, const int n)
      : FunctionalQuasigroupFactory(k, n) {}

  PFQuasigroup *create() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_PFQUASIGROUPFACTORY_H